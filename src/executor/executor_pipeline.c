/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:42:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 15:15:05 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"
#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void	child_process(t_exec *exec, t_shell *shell)
{
	int	ret;

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

int	wait_children()
{
	int	status;
	int	saved;

	saved = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			saved = WEXITSTATUS(status);
	}
	return (saved);
}

int	pipeline(t_exec *exec, t_shell *shell)
{
	t_command	*cmd;
	pid_t		pid;

	cmd = shell->commands;
	while (!shell->should_exit && cmd)
	{
		exec->cmd = cmd;
		exec->last = (cmd->next == NULL);
		if (is_builtin(exec->cmd->argv[0]) && is_single_command(shell->commands))
			return (execute_single_builtin(exec, shell));
		else
		{
			if (!exec->last && pipe(exec->pipe_fd) == -1)
				return (print_err_exit("pipe", strerror(errno), EXIT_FAILURE));
			pid = fork();
			if (pid == -1)
				return (print_err_exit("fork", strerror(errno), EXIT_FAILURE));
			else if (pid == 0)
				child_process(exec, shell);
			else
				parent_process(exec);
		}
		cmd = cmd->next;
	}
	return (wait_children());
}
