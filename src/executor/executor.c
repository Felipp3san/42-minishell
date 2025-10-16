/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:41:51 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/16 18:56:07 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"
#include "env.h"

int	g_last_exit_code;

int	execute(t_shell *shell)
{
	t_exec	exec;

	init_exec(&exec);
	shell->env_arr = env_list_to_arr(shell->env_lst);
	if (!shell->env_arr)
		return (ERROR);
	if (is_single_cmd(shell->commands) && !shell->commands->argv[0])
		return (SUCCESS);
	return (pipeline(&exec, shell));
}
