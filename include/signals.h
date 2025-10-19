/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:39:19 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 13:05:35 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal;

typedef enum e_sig_modes
{
	PROMPT_MODE,
	HEREDOC_MODE,
	EXEC_MODE_CHILD,
	EXEC_MODE_PARENT,
	IGNORE_MODE,
}	t_sig_modes;

void	set_signal_mode(int mode);

#endif
