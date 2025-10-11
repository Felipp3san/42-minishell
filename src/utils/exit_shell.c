/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 20:36:04 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 20:36:56 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	exit_shell(t_shell *shell, int err_code)
{
	if (shell)
		free_shell(shell, TRUE);
	exit (err_code);
}
