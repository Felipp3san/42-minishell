/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 20:52:09 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "signals.h"
#include "libft.h"
#include "tokenizer.h"
#include "ui.h"

void	free_exit(t_shell *shell)
{
	tokens_free(shell->tokens);
	if (shell->current_dir)
		free(shell->current_dir);
}

void	print_tokens(t_shell *shell)
{
	size_t	i;
	
	i = 0;
	if (shell->tokens->tokens)
	{
		while (shell->tokens->tokens[i])
			ft_printf("%s\n", shell->tokens->tokens[i++]);
	}
}

void	minishell_loop(t_shell	*shell)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			free_exit(shell);
			break ; // EOF (CTRL + D)
		}
		if (*input)
		{
			add_history(input);
			shell->tokens = tokenizer(input);
			if (!shell->tokens)
				free_exit(shell);
			print_tokens(shell);
		}
		tokens_free(shell->tokens); 
		free(input);
	}
}

int	init_shell(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ERROR);
	shell->current_dir = cwd;
	shell->last_exit_status = errno;
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
	return (EXIT_SUCCESS);
}
