/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:40:11 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 15:12:44 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"
#include "parser.h"
#include <unistd.h>

void	init_exec(t_exec *exec)
{
	exec->input_fd = STDIN_FILENO;
	exec->output_fd = STDOUT_FILENO;
	exec->pipe_fd[READ] = -1;
	exec->pipe_fd[WRITE] = -1;
	exec->last = FALSE;
	exec->cmd = NULL;
}

t_bool	is_builtin(char *cmd)
{
	const char	*builtins[] = {
		"echo",
		"cd",
		"env",
		"exit",
		"export",
		"pwd",
		"unset",
		NULL
	};
	size_t		i;

	if (!cmd)
		return (FALSE);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], cmd) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_single_cmd(t_command *commands)
{
	return (cmd_lst_size(commands) == 1);
}
