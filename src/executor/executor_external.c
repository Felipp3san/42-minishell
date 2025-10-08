/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:34:05 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 15:54:14 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "executor_internal.h"
#include "utils.h"
#include "path.h"

int	execute_external(t_exec *exec)
{
	pid_t	pid;

	pid = fork_child(exec);
	if (pid == -1)
		return (ERROR);
	return (SUCCESS);
}

static void	execute(t_exec *exec)
{
	char	*path;

	path = path_find(exec->cmd->argv[0], exec->envp);
	if (!path)
	{
		print_error("command not found", exec->cmd->argv[0]);
		exit(127);
	}
	execve(path, exec->cmd->argv, exec->envp);
	print_error(exec->cmd->argv[0], strerror(errno));
	if (errno == ENOENT)
		exit(127);
	exit(EXIT_FAILURE);
}

int	fork_child(t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		if (exec->input_fd != -1)
		{
			dup2(exec->input_fd, STDIN_FILENO);
			close(exec->input_fd);
		}
		if (exec->output_fd != -1)
		{
			dup2(exec->output_fd, STDOUT_FILENO);
			close(exec->output_fd);
		}
		execute(exec);
	}
	return (SUCCESS);
}
