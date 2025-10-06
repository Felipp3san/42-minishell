/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/05 15:03:01 by fde-alme         ###   ########.fr       */
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
#include "env.h"
#include "executor.h"
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
	{
		ft_lstclear(&shell->tokens, free);
		shell->tokens = NULL;
	}
	if (shell->commands)
	{
		ft_lstclear(&shell->commands, free_command);
		shell->commands = NULL;
	}
	if (full_cleaning)
	{
		if (shell->current_dir)
		{
			free(shell->current_dir);
			shell->current_dir = NULL;
		}
		if (shell->env)
		{
			ft_lstclear(&shell->env, free);
			shell->env = NULL;
		}
		rl_clear_history();
	}
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
	shell->env = env_clone(envp);
	if (!shell->env)
		return (ERROR);
	return (SUCCESS);
}

int	minishell_loop(t_shell	*shell)
{
	int	status;

	while (shell->should_exit == FALSE)
	{
		shell->user_input = readline(PROMPT);
		if (!shell->user_input)
		{
			status = builtin_exit(NULL);
			free_shell(shell, TRUE);
			exit(status);
		}
		else if (*shell->user_input)
		{
			add_history(shell->user_input);
			if (!tokenize(shell->user_input, &shell->tokens))
				return (free_shell(shell, TRUE), ERROR);
			if (!parse(shell->tokens, &shell->commands))
				return (free_shell(shell, TRUE), ERROR);
			if (executor(shell) != SUCCESS)
				return (free_shell(shell, TRUE), ERROR);
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
	print_banner();
	minishell_loop(&shell);
	free_shell(&shell, TRUE);
	return (g_last_exit_code);
}
