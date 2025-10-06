/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:41:51 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 21:41:52 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "executor.h"
#include "minishell.h"
#include "command.h"
#include "env.h"
#include "builtins.h"
#include "utils.h"

int	g_last_exit_code;

int	execute_builtin(t_shell *shell, t_command *command)
{
	int		status;
	char	*cmd_name;

	cmd_name = command->argv[0];
	if (ft_strcmp(cmd_name, "echo") == 0)
	{
		ft_printf("echo");
		return (SUCCESS);
	}
	else if (ft_strcmp(cmd_name, "exit") == 0)
	{
		status = builtin_exit(command->argv);
		if (status != ERROR)
		{
			shell->should_exit = TRUE;
			g_last_exit_code = status;
		}
		return (SUCCESS);
	}
	else 
		return (ERROR);
}

int	execute_external(t_command *cmd, char **envp)
{
	char	*path;
	//TODO: FIND PATH
	path = "/bin/ls";
	if (!path)
	{
		print_error("command not found", cmd->argv[0]);
		g_last_exit_code = 127;
	}
	execve(path, cmd->argv, envp);
	if (errno == ENOENT)
		g_last_exit_code = 127;
	g_last_exit_code = EXIT_FAILURE;
	return (ERROR);
}

int	create_child_process(t_command *cmd, char **envp, t_bool last)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
		return (ERROR);
	pid = fork();
	if (pid == -1)
		return (ERROR);
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		if (!last)
			dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		execute_external(cmd, envp);
	}
	else
	{
		if (!last)
			dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		waitpid(pid, NULL, 0);
	}
	return (SUCCESS);
}

int	executor(t_shell *shell)
{
	char		**envp;
	t_list		*node;
	t_status	status;
	
	status = SUCCESS;
	envp = env_list_to_arr(shell->env);
	if (!envp)
		return (ERROR);
	node = shell->commands;
	while (shell->should_exit == FALSE && status != ERROR && node)
	{
		//if (ft_lstsize(shell->commands) == 1)
		//	status = execute_builtin(shell, node->content);
		if (node->next == NULL)
			create_child_process(node->content, envp, TRUE);
		else
			create_child_process(node->content, envp, FALSE);
		node = node->next;
	}
	env_free(envp);
	return (SUCCESS);
}
