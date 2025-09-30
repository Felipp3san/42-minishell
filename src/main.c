/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 14:10:56 by fde-alme         ###   ########.fr       */
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
#include "ui.h"

//void	free_shell(t_shell *shell, t_bool free_cwd)
//{
//	if (!shell)
//		return ;
//	if (shell->tokens)
//	{
//		tokens_free(shell->tokens);
//		free(shell->tokens);
//		shell->tokens = NULL;
//	}
//	if (free_cwd && shell->current_dir)
//	{
//		free(shell->current_dir);
//		shell->current_dir = NULL;
//	}
//}

int	init_shell(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ERROR);
	shell->tokens->next = NULL;
	shell->current_dir = cwd;
	shell->last_exit_status = errno;
	return (SUCCESS);
}

void	minishell_loop(t_shell	*shell)
{
	char	*input;

	while (TRUE)
	{
		input = readline(PROMPT);
		if (!input)
		{
			//free_shell(shell);
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (tokenize(input, &shell->tokens) != SUCCESS)
			{
				tokens_free(&shell->tokens);
				free(input);
				break ;
			}
			if (!shell->tokens)
			{
				//free_shell(shell);
				free(input);
				break ;
			}
			//if (parser());
			//if (executor());
			tokens_free(&shell->tokens);
			free(input);
		}
	}
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
	//free_shell(shell);
	return (EXIT_SUCCESS);
}
