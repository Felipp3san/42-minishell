/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:40:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/05 14:38:52 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "libft.h"
# include "types.h"
# include "command.h"

// parser_create.c
t_redir		*redir_create(char *filename, t_type type);
t_command	*command_create(void);
t_command	*argv_append(t_command *command, const char *str);
t_command	*argv_realloc(t_command *command);

// parser_free.c
void		free_argv(t_command	*command);
void		free_command(void *content);
void		free_redir(void *content);

// parser_utils.c
t_bool		is_word(t_type type);
t_bool		is_redir(t_type type);
t_type		get_token_type(char *str);
void		move_forward(t_list **start, size_t count);

#endif
