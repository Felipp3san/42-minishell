/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:08:26 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 19:09:50 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include "types.h"

static void	sigint_handler(int sig);

int	init_parent_signals(void)
{
	struct sigaction	sigint;
	struct sigaction	sigquit;

	sigint.sa_handler = sigint_handler;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = 0;
	sigquit.sa_handler = SIG_IGN;
	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_flags = 0;
	if (sigaction(SIGINT, &sigint, NULL) == -1)
		return (ERR_SIGACTION);
	if (sigaction(SIGQUIT, &sigquit, NULL) == -1)
		return (ERR_SIGACTION);
	return (SUCCESS);
}

static void	sigint_handler(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
