/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 19:59:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "signals.h"
#include "tokenizer.h"
#include "parser.h"
#include "ui.h"
#include "types.h"
#include "expander.h"
#include "executor.h"
#include "builtins.h"
#include "debug.h"

int	get_input(t_shell *shell)
{
	shell->user_input = readline(PROMPT);
	if (!shell->user_input)
		builtin_exit(NULL, shell);
	if (!*shell->user_input)
		return (ERROR);
	return (SUCCESS);
}

int	process_input(t_shell *shell)
{
	shell->tokens = tokenize(shell->user_input);
	if (!shell->tokens)
		return (ERROR);
	//print_token_list(shell->tokens);
	shell->commands = parse(shell->tokens);
	if (!shell->commands)
		return (ERROR);
	//print_command_list(shell->commands);
	if (!expand(shell))
		return (ERROR);
	//print_command_list(shell->commands);
	shell->last_exit_code = execute(shell);
	return (SUCCESS);
}

int	minishell_loop(t_shell	*shell)
{
	while (shell->should_exit == FALSE)
	{
		if (get_input(shell) == SUCCESS)
		{
			add_history(shell->user_input);
			if (process_input(shell) == ERROR)
			{
				free_shell(shell, FALSE);
				continue ;
			}
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
	return (shell.last_exit_code);
}
