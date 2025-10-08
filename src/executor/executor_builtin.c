/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:34:24 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 14:47:20 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor_internal.h"

int	execute_builtin(t_exec *exec, t_shell *shell)
{
	t_command	*cmd;
	pid_t		pid;
	int			error_code;

	cmd = exec->cmd;
	if (cmd && cmd->argv)
	{
		if (ft_strcmp(cmd->argv[0], "exit") == 0)
		{
			error_code = builtin_exit(cmd->argv);
			if (error_code == ERROR)
				return (ERROR);
			shell->should_exit = TRUE;
			return (error_code);
		}
		else
		{
			pid = fork_child(exec);
			if (pid == -1)
				return (ERROR);
		}
	}
	return (SUCCESS);
}
