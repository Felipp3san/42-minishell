/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:31:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 23:16:47 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include "tokens.h"

# define PROMPT "\001\033[1;36m\002minishell>\001\033[0m\002 "

typedef struct s_shell
{
	t_tokens	*tokens;
	char		*current_dir;
	int			last_exit_status;
}	t_shell;

#endif
