/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/16 17:51:01 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "parser/parser_internal.h"
#include "signals.h"
#include "tokenizer.h"
#include "parser.h"
#include "ui.h"
#include "types.h"
#include "env.h"
#include "expander.h"
#include "executor.h"
#include "debug.h"
#include "builtins.h"

void	free_shell(t_shell *shell, t_bool full_cleaning)
{
	if (!shell)
		return ;
	if (shell->user_input)
	{
		free(shell->user_input);
		shell->user_input = NULL;
	}
	if (shell->tokens)
		token_lst_clear(&shell->tokens);
	if (shell->commands)
		cmd_lst_clear(&shell->commands);
	if (shell->env_arr)
	{
		env_free(shell->env_arr);
		shell->env_arr = NULL;
	}
	if (full_cleaning)
		full_clean(shell);

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
	shell->env_lst = env_arr_to_lst(envp);
	if (!shell->env_lst)
		return (ERROR);
	shell->env_arr = NULL;
	return (SUCCESS);
}

int	minishell_loop(t_shell	*shell)
{
	while (shell->should_exit == FALSE)
	{
		shell->user_input = readline(PROMPT);
		if (!shell->user_input)
			builtin_exit(NULL, shell);
		else if (*shell->user_input)
		{
			add_history(shell->user_input);
			if (get_commands(shell) != SUCCESS)
				continue ;
			expand(shell);
			g_last_exit_code = execute(shell);
		}
		free_shell(shell, FALSE);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void) argc;
	(void) argv;
	if (init_shell(&shell, envp) != SUCCESS)
		return (free_shell(&shell, TRUE), EXIT_FAILURE);
	if (init_parent_signals() != SUCCESS)
		return (free_shell(&shell, TRUE), EXIT_FAILURE);
	//print_banner();
	minishell_loop(&shell);
	free_shell(&shell, TRUE);
	return (g_last_exit_code);
}
