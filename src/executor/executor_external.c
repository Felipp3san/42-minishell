/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:34:05 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:41:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "executor_internal.h"
#include "utils.h"
#include "path.h"

int	is_dir(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

void	execute_external(t_exec *exec, t_shell *shell)
{
	char		*path;
	t_command	*cmd;

	cmd = exec->cmd;
	shell->env_arr = env_list_to_arr(shell->env_lst);
	if (!shell->env_arr)
		print_exit(shell, "env_list_to_arr", "copy failed", EXIT_FAILURE);
	path = path_find(cmd->argv[0], shell->env_arr);
	if (!path)
		print_exit(shell, cmd->argv[0], "command not found", CMD_NOT_FOUND);
	if (is_dir(path))
	{
		free(path);
		print_exit(shell, cmd->argv[0], "Is a directory", CMD_NOT_EXEC);
	}
	if (execve(path, cmd->argv, shell->env_arr) == -1)
	{
		print_error(cmd->argv[0], strerror(errno), NULL);
		free(path);
		if (errno == ENOENT)
			exit_shell(shell, CMD_NOT_FOUND);
		if (errno == EACCES)
			exit_shell(shell, CMD_NOT_EXEC);
		exit_shell(shell, EXIT_FAILURE);
	}
}
