/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 19:10:25 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
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

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
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
	if (shell->current_dir)
	{
		free(shell->current_dir);
		shell->current_dir = NULL;
	}
}

int	init_shell(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ERROR);
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->current_dir = cwd;
	shell->last_exit_status = errno;
	return (SUCCESS);
}

int	minishell_loop(t_shell	*shell)
{
	char	*input;

	while (TRUE)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			if (!tokenize(input, &shell->tokens))
			{
				free(input);
				return (free_shell(shell), ERROR);
			}
			if (!parse(shell->tokens, &shell->commands))
			{
				free(input);
				return (free_shell(shell), ERROR);
			}
			free(input);
		}
	}
	return (SUCCESS);
}

int	main(void)
{
	t_shell	shell;

	if (init_shell(&shell) != SUCCESS)
		return (EXIT_FAILURE);
	if (init_parent_signals() != SUCCESS)
		return (EXIT_FAILURE);
	print_banner();
	minishell_loop(&shell);
	free_shell(&shell);
	return (EXIT_SUCCESS);
}
