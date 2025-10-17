/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:16:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 11:13:43 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

#include <stddef.h>
#include "token.h"

typedef struct s_redir
{
	char				*value;
	t_token_type		type;
	int					heredoc_fd;
	int					expand_heredoc;
	struct s_redir		*next;
	struct s_redir		*previous;
}	t_redir;

typedef struct s_redir_data
{
	char				*value;
	int					heredoc_fd;
	int					expand_heredoc;
	t_token_type		type;
}	t_redir_data;

typedef struct s_command
{
	char				**argv;
	size_t				size;
	size_t				capacity;
	t_redir				*redirs;
	struct s_command	*next;
	struct s_command	*previous;
}	t_command;

// cmd_utils.c
t_command	*cmd_lst_new(void);
void		cmd_lst_add_back(t_command **cmd_list, t_command *new_cmd);
void		cmd_lst_clear(t_command **cmd);
void		cmd_lst_delone(t_command **cmd);

// redir_utils.c
t_redir		*redir_lst_new(t_redir_data *data, t_token_type type);
void		redir_lst_add_back(t_redir **redir_list, t_redir *new_redir);
void		redir_lst_clear(t_redir **redir);

// argv_utils.c
t_command	*argv_append(t_command *command, const char *str);
t_command	*argv_realloc(t_command *command);

#endif
