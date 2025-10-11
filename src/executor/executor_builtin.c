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

#include "executor_internal.h"
#include "builtins.h"
#include "utils.h"
#include <string.h>
#include <unistd.h>

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

int	execute_single_builtin(t_exec *exec, t_shell *shell)
{
	int	ret;
	int	saved_in;
	int	saved_out;

	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (apply_redirections(exec) == ERROR)
		return (print_err_exit("redir", strerror(errno), EXIT_FAILURE));
	ret = execute_builtin(exec, shell);
	dup2(saved_in, STDIN_FILENO);
	close(saved_in);
	dup2(saved_out, STDOUT_FILENO);
	close(saved_out);
	return (ret);
}
