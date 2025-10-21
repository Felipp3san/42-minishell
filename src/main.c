/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/21 16:47:49 by jfernand         ###   ########.fr       */
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
#include "heredoc.h"

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
	shell->commands = parse(shell->tokens);
	if (!shell->commands)
		return (ERROR);
	if (heredoc_handle(shell) != SUCCESS)
		return (ERROR);
	if (!expand(shell))
		return (ERROR);
	shell->last_exit_code = execute(shell);
	return (SUCCESS);
}

int	minishell_loop(t_shell	*shell)
{
	while (TRUE)
	{
		g_signal = 0;
		set_signal_mode(PROMPT_MODE);
		if (get_input(shell) == SUCCESS)
		{
			add_history(shell->user_input);
			process_input(shell);
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
	print_banner();
	minishell_loop(&shell);
	free_shell(&shell, TRUE);
	return (shell.last_exit_code);
}
