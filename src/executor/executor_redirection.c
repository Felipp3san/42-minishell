/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:36:20 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 14:42:18 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "executor_internal.h"
#include "utils.h"

static int	open_input(char *filename);
static int	open_output(char *filename, t_bool append);

int	setup_redirs(t_exec *exec)
{
	t_list	*redir_node;
	t_redir	*redir;
	int		fd;

	if (exec->cmd->redirs)
	{
		redir_node = exec->cmd->redirs;
		while (redir_node)
		{
			redir = (t_redir *) redir_node->content;
			if (redir->type == INPUT)
			{
				fd = open_input(redir->filename);
				if (fd == -1)
					return (ERROR);
				exec->input_fd = fd;
			}
			else if (redir->type == OUTPUT)
			{
				fd = open_output(redir->filename, FALSE);
				if (fd == -1)
					return (ERROR);
				exec->output_fd = fd;
			}
			else if (redir->type == APPEND)
			{
				fd = open_output(redir->filename, TRUE);
				if (fd == -1)
					return (ERROR);
				exec->output_fd = fd;
			}
			else if (redir->type == HEREDOC)
			{
				if (exec->input_fd != -1)
					close(exec->input_fd);
				exec->input_fd = heredoc(redir->delimiter);
				if (exec->input_fd == -1)
					return (ERROR);
			}
			redir_node = redir_node->next;
		}
	}
	return (SUCCESS);
}

static int	open_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
	{
		print_error(strerror(errno), filename, NULL);
		return (EXIT_FAILURE);
	}
	return (fd);
}

static int	open_output(char *filename, t_bool append)
{
	int	fd;

	if (append)
		fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		print_error(strerror(errno), filename, NULL);
		return (EXIT_FAILURE);
	}
	return (fd);
}
