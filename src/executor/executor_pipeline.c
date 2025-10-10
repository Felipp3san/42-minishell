/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 14:42:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 15:58:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"
#include "utils.h"

int	pipeline(t_exec *exec, t_shell *shell)
{
	int		pipe_fd[2];
	t_list	*cmd_node;

	cmd_node = shell->commands;
	while (!shell->should_exit && cmd_node)
	{
		exec->last = (cmd_node->next == NULL);
		exec->cmd = (t_command *)cmd_node->content;

		if (!exec->last && pipe(pipe_fd) == -1)
			return (ERROR);
		if (!exec->last)
			exec->output_fd = pipe_fd[WRITE];
		else
			exec->output_fd = -1;
		if (setup_redirs(exec) == ERROR)
			print_error("redirs", "redirection setup failed", NULL);
		if (is_builtin(exec->cmd))
			execute_builtin(exec, shell);
		else
			execute_external(exec);
		if (exec->input_fd != -1)
		{
			close(exec->input_fd);
			exec->input_fd = -1;
		}
		if (!exec->last)
		{
			close(pipe_fd[WRITE]);
			exec->input_fd = pipe_fd[READ];
		}
		cmd_node = cmd_node->next;
	}
	return (SUCCESS);
}
