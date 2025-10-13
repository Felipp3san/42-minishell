/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:41:51 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 21:33:21 by fde-alme         ###   ########.fr       */
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
	return (pipeline(&exec, shell));
}
