/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:34:24 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/16 18:46:56 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"
#include "builtins.h"
#include <unistd.h>

int	execute_builtin(t_exec *exec, t_shell *shell)
{
	t_command	*cmd;

	cmd = exec->cmd;
	if (!cmd && !cmd->argv[0])
		return (ERROR);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd, shell));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv, &shell->env_lst));
	if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (builtin_env(shell->env_lst));
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (builtin_export(&shell->env_lst, cmd->argv[1]));
	if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (builtin_unset(&shell->env_lst, cmd->argv[1]));
	return (CMD_NOT_FOUND);
}

int	execute_single_builtin(t_exec *exec, t_shell *shell)
{
	int	ret;
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(exec) == ERROR)
	{
		close(saved_in);
		close(saved_out);
		return (EXIT_FAILURE);
	}
	ret = execute_builtin(exec, shell);
	dup2(saved_in, STDIN_FILENO);
	close(saved_in);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_out);
	return (ret);
}
