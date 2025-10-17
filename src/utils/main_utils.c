/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:36 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/17 11:09:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "token.h"

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
		env_free(shell->env_arr);
		shell->env_arr = NULL;
	}
	if (!full_clean)
		return ;
	free_ptr((void **) &shell->current_dir);
	env_lst_clear(&shell->env_lst);
	rl_clear_history();
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
		return (ERROR);
	shell->env_arr = NULL;
	return (SUCCESS);
}
