/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:40:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/10 13:46:06 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "types.h"
# include "token.h"
# include "command.h"

// parser_cmd_list.c
t_command	*cmd_lst_new(void);
void		cmd_lst_add_back(t_command **cmd_list, t_command *new_cmd);
void		cmd_lst_clear(t_command **cmd);
void		cmd_lst_delone(t_command **cmd);

// parser_redir_list.c
t_redir		*redir_lst_new(char *value, int heredoc_fd, t_token_type type);
void		redir_lst_add_back(t_redir **redir_list, t_redir *new_redir);
void		redir_lst_clear(t_redir **redir);

// parser_argv.c
t_command	*argv_append(t_command *command, const char *str);
t_command	*argv_realloc(t_command *command);

// parser_heredoc.c
int			parser_heredoc(char *delimiter);

// parser_utils.c
void		print_parser_err(t_token *error);
t_bool		is_redir(t_token_type type);
t_bool		is_sep(t_token_type type);
t_bool		is_word(t_token_type type);
t_bool		is_heredoc(t_token_type type);

#endif
