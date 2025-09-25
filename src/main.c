/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:25:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 18:26:45 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "token.h"
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int	init_signals()
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	// SIGINT
	sigint.sa_handler = sigint_handler;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;

	// SIGQUIT
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;

	if (sigaction(SIGINT, &sigint, NULL) == -1)
		return (ERR_SIGACTION);
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
		return (ERR_SIGACTION);
	return (SUCCESS);
}

void	minishell_loop(t_shell	*shell)
{
	char	*input;
	t_token	tokens;

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
			tokens = tokenizer(input, shell);
			while (*tokens)
			{
				ft_printf("%s\n", *tokens);
				tokens++;
			}
			tokens_print(shell->tokens);
		}
		free_tokens(shell); 
		free(input);
	}
}

int	init_shell(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (ERROR);
	shell->tokens = NULL;
	shell->token_count = 0;
	shell->current_dir = cwd;
	shell->last_exit_status = errno;
	return (SUCCESS);
}

int	main(void)
{
	t_shell	shell;

	if (init_shell(&shell) != SUCCESS)
		return (EXIT_FAILURE);
	if (init_signals() != SUCCESS)
		return (EXIT_FAILURE);
	print_banner();
	minishell_loop(&shell);
	return (EXIT_SUCCESS);
}
