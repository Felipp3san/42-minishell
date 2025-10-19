/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:08:26 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:47:12 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signals.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

volatile sig_atomic_t g_signal = 0;

void	handle_sigint_sigquit_exec(int sig)
{
	g_signal = sig;
	if (sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit\n", 5);
	if (sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigint_prompt(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint_heredoc(int sig)
{
	g_signal = sig;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

void	set_signal_mode(int mode)
{
	if (mode == PROMPT_MODE)
	{
		signal(SIGINT, handle_sigint_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == HEREDOC_MODE)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == EXEC_MODE_PARENT)
	{
		signal(SIGINT, handle_sigint_sigquit_exec);
		signal(SIGQUIT, handle_sigint_sigquit_exec);
	}
	else if (mode == EXEC_MODE_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (mode == IGNORE_MODE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
