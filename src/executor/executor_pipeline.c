/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:42:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 13:04:09 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include "executor_internal.h"
#include "signals.h"
#include "utils.h"

void	child_process(t_exec *exec, t_shell *shell)
{
	int	ret;

	set_signal_mode(EXEC_MODE_CHILD);
	if (exec->input_fd != STDIN_FILENO)
	{
		dup2(exec->input_fd, STDIN_FILENO);
		close(exec->input_fd);
	}
	if (!exec->last)
	{
		dup2(exec->pipe_fd[WRITE], STDOUT_FILENO);
		close(exec->pipe_fd[READ]);
		close(exec->pipe_fd[WRITE]);
	}
	if (apply_redirections(exec) == ERROR)
		exit_shell(shell, EXIT_FAILURE);
	if (is_builtin(exec->cmd->argv[0]))
	{
		ret = execute_builtin(exec, shell);
		exit_shell(shell, ret);
	}
	else
		execute_external(exec, shell);
}

void	parent_process(t_exec *exec)
{
	if (exec->input_fd != STDIN_FILENO)
		close(exec->input_fd);
	if (!exec->last)
	{
		close(exec->pipe_fd[WRITE]);
		exec->input_fd = exec->pipe_fd[READ];
	}
}

int	wait_children(pid_t last_pid)
{
	int	pid;
	int	status;
	int	saved;

	saved = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				saved = WEXITSTATUS(status);
		}
		pid = wait(&status);
	}
	return (saved);
}

int	pipeline(t_exec *exec, t_shell *shell)
{
	pid_t	pid;
	pid_t	last_pid;

	while (exec->cmd)
	{
		exec->last = (exec->cmd->next == NULL);
		if (!exec->last && pipe(exec->pipe_fd) == -1)
			return (print_error_return("pipe", strerror(errno), EXIT_FAILURE));
		pid = fork();
		if (pid == -1)
			return (print_error_return("fork", strerror(errno), EXIT_FAILURE));
		else if (pid == 0)
			child_process(exec, shell);
		else
			parent_process(exec);
		if (exec->last)
			last_pid = pid;
		exec->cmd = exec->cmd->next;
	}
	return (wait_children(last_pid));
}
