/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:36 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/17 12:37:48 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "env.h"
#include "minishell.h"
#include "token.h"
#include "builtins.h"

void	free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_shell(t_shell *shell, t_bool full_clean)
{
	if (!shell)
		return ;
	free_ptr((void **) &shell->user_input);
	token_lst_clear(&shell->tokens);
	cmd_lst_clear(&shell->commands);
	if (shell->env_arr)
	{
		env_arr_free(shell->env_arr);
		shell->env_arr = NULL;
	}
	if (!full_clean)
		return ;
	free_ptr((void **) &shell->current_dir);
	env_lst_clear(&shell->env_lst);
	rl_clear_history();
}

static int	initialize_env(t_shell *shell)
{
	char	*pwd;
	char	*cwd;
	t_env	*node;

	pwd = ft_strdup("PWD");
	if (!pwd)
		return (ERROR);
	cwd = ft_strdup(shell->current_dir);
	if (!cwd)
		return (free(pwd), ERROR);
	node = env_lst_new(pwd, cwd);
	env_lst_add_back(&shell->env_lst, node);
	return (SUCCESS);
};

void	increment_shlvl(t_shell *shell)
{
	t_env	*env_node;
	int		new_value;
	char	*tmp;

	env_node = search_variable(shell->env_lst, "SHLVL", 0);
	if (!env_node)
	{
		add_variable(&shell->env_lst, ft_strdup("SHLVL"),
				ft_strdup("1"), 0);
		return ;
	}
	if (env_node->value)
		new_value = ft_atoi(env_node->value) + 1;
	else
		new_value = 0;
	if (new_value < 0)
		new_value = 0;
	else if (new_value >= 1000)
		new_value = 1;
	tmp = ft_itoa(new_value);
	replace_variable(env_node, tmp);
}

int	init_shell(t_shell *shell, char **envp)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ERROR);
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->current_dir = cwd;
	shell->should_exit = FALSE;
	shell->last_exit_code = 0;
	shell->env_lst = env_arr_to_lst(envp);
	if (!shell->env_lst)
		if (initialize_env(shell) == ERROR)
			return (ERROR);
	increment_shlvl(shell);
	shell->env_arr = NULL;
	return (SUCCESS);
}
