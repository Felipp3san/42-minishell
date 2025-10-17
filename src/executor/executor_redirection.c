/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:36:20 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:42:37 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "executor_internal.h"
#include "command.h"
#include "types.h"
#include "utils.h"

static int	open_input(char *value);
static int	open_output(char *value, int append);

static int	handle_output(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == OUTPUT)
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
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (SUCCESS);
}

static int	handle_input(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == INPUT)
	{
		fd = open_input(redir->value);
		if (fd == ERROR)
			return (ERROR);
	}
	else if (redir->type == HEREDOC)
	{
		fd = redir->heredoc_fd;
		redir->heredoc_fd = -1;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (SUCCESS);
}

int	apply_redirections(t_exec *exec)
{
	t_redir	*redir;
	int		status;

	if (exec->cmd->redirs)
	{
		redir = exec->cmd->redirs;
		while (redir)
		{
			if (redir->type == INPUT || redir->type == HEREDOC)
				status = handle_input(redir);
			else
				status = handle_output(redir);
			if (status != SUCCESS)
				return (ERROR);
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
		print_error(value, strerror(errno), NULL);
		return (ERROR);
	}
	return (fd);
}

static int	open_output(char *value, int append)
{
	int	fd;

	if (append)
		fd = open(value, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(value, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		print_error(value, strerror(errno), NULL);
		return (ERROR);
	}
	return (fd);
}
