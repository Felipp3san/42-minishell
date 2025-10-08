/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:40:11 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 15:28:59 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"

void	init_exec(t_exec *exec)
{
	exec->input_fd = -1;
	exec->output_fd = -1;
	exec->pipe_fd[READ] = -1;
	exec->pipe_fd[WRITE] = -1;
	exec->last = FALSE;
	exec->envp = NULL;
	exec->cmd = NULL;
}

t_bool	is_builtin(t_command *command)
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

	if (!command || !command->argv)
		return (FALSE);
	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(builtins[i], command->argv[0]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_single_command(t_list *commands)
{
	return (ft_lstsize(commands) == 1);
}
