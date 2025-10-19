/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:41:51 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:37:03 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"
#include "env.h"
#include "signals.h"

int	execute(t_shell *shell)
{
	t_exec	exec;

	set_signal_mode(EXEC_MODE_PARENT);
	init_exec(&exec, shell);
	shell->env_arr = env_list_to_arr(shell->env_lst);
	if (!shell->env_arr)
		return (ERROR);
	if (is_single_cmd(shell->commands) && !shell->commands->argv[0])
		return (SUCCESS);
	else if (is_single_cmd(shell->commands)
		&& is_builtin(exec.cmd->argv[0]))
		return (execute_single_builtin(&exec, shell));
	else
		return (pipeline(&exec, shell));
}
