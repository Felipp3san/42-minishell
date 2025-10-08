/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:39:41 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 14:39:51 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "types.h"

int	heredoc(char *delimiter)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (ERROR);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
	{
		close(pipe_fd[READ]);
		while (TRUE)
		{
			line = readline("> ");
			if (!line)
			{
				ft_dprintf(2, "minishell: warning: here-document delimited by end-of-file: wanted(`%s')\n", delimiter);
				close(pipe_fd[WRITE]);
				exit(EXIT_FAILURE);
			}
			if (ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				close(pipe_fd[WRITE]);
				exit(EXIT_SUCCESS);
			}
			add_history(line);
			write(pipe_fd[WRITE], line, ft_strlen(line));
			write(pipe_fd[WRITE], "\n", 1);
			free(line);
		}
	}
	close(pipe_fd[WRITE]);
	waitpid(pid, NULL, 0);
	return (pipe_fd[READ]);
}
