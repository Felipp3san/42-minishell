/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:34:05 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 22:07:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "executor_internal.h"
#include "utils.h"
#include "path.h"

void	execute_external(t_exec *exec, t_shell *shell)
{
	char	*path;

	path = path_find(exec->cmd->argv[0], shell->env_arr);
	if (!path)
	{
		print_error(exec->cmd->argv[0], "command not found", NULL);
		exit_shell(shell, CMD_NOT_FOUND);
	}
	if (execve(path, exec->cmd->argv, shell->env_arr) == -1)
	{
		print_error(exec->cmd->argv[0], strerror(errno), NULL);
		free(path);
		if (errno == ENOENT)
			exit_shell(shell, CMD_NOT_FOUND);
		exit_shell(shell, EXIT_FAILURE);
	}
}
