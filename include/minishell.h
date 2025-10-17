/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:31:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 11:10:57 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include "types.h"
# include "command.h"
# include "token.h"
# include "env.h"

typedef struct s_shell
{
	char		*current_dir;
	char		*user_input;
	t_token		*tokens;
	t_command	*commands;
	t_env		*env_lst;
	char		**env_arr;
	t_bool		should_exit;
	int			last_exit_code;
}	t_shell;

//main.c
void	free_shell(t_shell *shell, t_bool full_cleaning);

//main_utils.c
void	full_clean(t_shell *shell);

#endif
