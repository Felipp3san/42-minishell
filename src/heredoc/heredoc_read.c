/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:32:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:37:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "heredoc_internal.h"
#include "minishell.h"
#include "signals.h"
#include "libft.h"
#include "types.h"

static int	child_exit_code(void)
{
	if (g_signal == SIGINT)
		return (128 + SIGINT);
	return (EXIT_SUCCESS);
}

static int	child_heredoc(t_shell *shell, int pipe_fd[], char *delimiter)
{
	char	*line;

	set_signal_mode(HEREDOC_MODE);
	close(pipe_fd[READ]);
	while (TRUE)
	{
		line = readline("> ");
		if (!line || g_signal == SIGINT)
		{
			if (!g_signal)
				print_err_heredoc(delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[WRITE]);
		free(line);
	}
	close(pipe_fd[WRITE]);
	free_shell(shell, TRUE);
	return (child_exit_code());
}

static int	parent_heredoc(t_shell *shell, int pipe_fd[], int pid)
{
	int	status;

	close(pipe_fd[WRITE]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 128 + SIGINT)
	{
		shell->last_exit_code = 130;
		return (close(pipe_fd[READ]), ERROR);
	}
	return (pipe_fd[READ]);
}

int	heredoc_read(t_shell *shell, char *delimiter)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (ERROR);
	set_signal_mode(IGNORE_MODE);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		return (ERROR);
	}
	if (pid == 0)
		exit(child_heredoc(shell, pipe_fd, delimiter));
	else
		return (parent_heredoc(shell, pipe_fd, pid));
}
