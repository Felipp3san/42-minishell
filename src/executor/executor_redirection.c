/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:36:20 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/10 14:13:47 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include "executor_internal.h"
#include "utils.h"

static int	open_input(char *value);
static int	open_output(char *value, t_bool append);

int	apply_redirections(t_exec *exec)
{
	t_redir	*redir;
	int		fd;

	if (exec->cmd->redirs)
	{
		redir = exec->cmd->redirs;
		while (redir)
		{
			if (redir->type == INPUT)
			{
				fd = open_input(redir->value);
				if (fd == ERROR)
					return (ERROR);
			}
			else if (redir->type == OUTPUT)
			{
				fd = open_output(redir->value, FALSE);
				if (fd == ERROR)
					return (ERROR);
			}
			else if (redir->type == APPEND)
			{
				fd = open_output(redir->value, TRUE);
				if (fd == ERROR)
					return (ERROR);
			}
			else if (redir->type == HEREDOC)
			{
				fd = redir->heredoc_fd;
				redir->heredoc_fd = -1;
			}

			if (redir->type == INPUT || redir->type == HEREDOC)
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
		print_error("open_input", strerror(errno), value);
		return (ERROR);
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
		print_error("open_output", strerror(errno), value);
		return (ERROR);
	}
	return (fd);
}
