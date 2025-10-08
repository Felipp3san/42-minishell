/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:34:24 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 21:37:42 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "executor_internal.h"

int	execute_builtin(t_exec *exec, t_shell *shell)
{
	t_command	*cmd;

	cmd = exec->cmd;
	if (!cmd && !cmd->argv[0])
		return (ERROR);
	if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (builtin_exit(cmd->argv, shell));
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (builtin_echo(cmd->argv));
	if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (builtin_cd(cmd->argv));
	return (CMD_NOT_FOUND);
}
