/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:40:11 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:40:41 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "executor_internal.h"
#include "command.h"
#include "libft.h"
#include "builtins.h"

void	update_env(t_exec *exec, t_shell *shell, int last)
{
	t_command	*cmd;
	t_env		*node;
	char		*new_val;

	cmd = exec->cmd;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return ;
	if (last)
		new_val = ft_strdup(cmd->argv[cmd->size - 1]);
	else
		new_val = ft_strdup(cmd->argv[0]);
	if (!new_val)
		return ;
	node = search_variable(shell->env_lst, "_", 0);
	if (!node)
		add_variable(&shell->env_lst, ft_strdup("_"), new_val, 0);
	else
		replace_variable(node, new_val);
}

void	init_exec(t_exec *exec, t_shell *shell)
{
	exec->input_fd = STDIN_FILENO;
	exec->output_fd = STDOUT_FILENO;
	exec->pipe_fd[READ] = -1;
	exec->pipe_fd[WRITE] = -1;
	exec->last = FALSE;
	exec->cmd = shell->commands;
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

	if (!cmd || !*cmd)
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
