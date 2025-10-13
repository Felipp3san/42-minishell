/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:32:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 12:19:57 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "types.h"

static void	print_err_heredoc(const char *delimiter)
{
	ft_dprintf(2, "minishell: warning:"
		"here-document delimited by end-of-file: wanted(`%s')\n",
		delimiter);
}

int	parser_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (ERROR);
	while (TRUE)
	{
		line = readline("> ");
		if (!line)
		{
			print_err_heredoc(delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		add_history(line);
		write(pipe_fd[WRITE], line, ft_strlen(line));
		write(pipe_fd[WRITE], "\n", 1);
		free(line);
	}
	close(pipe_fd[WRITE]);
	return (pipe_fd[READ]);
}
