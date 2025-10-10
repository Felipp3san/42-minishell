/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:36:20 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 15:14:54 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "executor_internal.h"
#include "utils.h"

static int	open_input(char *value);
static int	open_output(char *value, t_bool append);

int	setup_redirs(t_exec *exec)
{
	t_redir	*redir;
	int		fd;

	if (exec->cmd->redirs)
	{
		redir = exec->cmd->redirs;
		while (redir)
		{
			if (redir->type == INPUT)
				fd = open_input(redir->value);
			else if (redir->type == OUTPUT)
				fd = open_output(redir->value, FALSE);
			else if (redir->type == APPEND)
				fd = open_output(redir->value, TRUE);
			else if (redir->type == HEREDOC)
			{
				exec->input_fd = heredoc(redir->value);
				if (exec->input_fd == -1)
					return (ERROR);
			}
			if (redir->type == INPUT)
				dup2(fd, STDIN_FILENO);
			else
				dup2(fd, STDOUT_FILENO);
			close(fd);
			redir = redir->next;
		}
	}
	return (SUCCESS);
}

static int	open_input(char *value)
{
	int	fd;

	fd = open(value, O_RDONLY, 0644);
	if (fd == -1)
	{
		print_error(strerror(errno), value, NULL);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static int	open_output(char *value, t_bool append)
{
	int	fd;

	if (append)
		fd = open(value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		print_error(strerror(errno), value, NULL);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
