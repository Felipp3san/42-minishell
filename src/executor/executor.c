/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:41:51 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:34:03 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_internal.h"
#include "signals.h"

int	execute(t_shell *shell)
{
	t_exec	exec;

	set_signal_mode(EXEC_MODE_PARENT);
	init_exec(&exec, shell);
	if (!shell->commands)
		return (SUCCESS);
	else
		return (pipeline(&exec, shell));
}
