/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:31:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 13:53:50 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include "types.h"
# include "libft.h"
# include "command.h"
# include "token.h"
# include "env.h"

extern int	g_last_exit_code;

typedef struct s_shell
{
	char		*current_dir;
	char		*user_input;
	t_token		*tokens;
	t_command	*commands;
	t_env		*env_lst;
	char		**env_arr;
	t_bool		should_exit;
}	t_shell;

void	free_shell(t_shell *shell, t_bool full_cleaning);

#endif
