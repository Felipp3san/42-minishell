/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:38:35 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 16:00:05 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

#include "libft.h"

typedef t_list t_commands;

/*
 * command = ["ls", "-la", NULL]
 * type = WORD
 * */

/*
 * command = ["|", NULL]
 * type = PIPE
 * */

/*
 * command = [">>", NULL]
 * type = OUT_APPEND
 * */

/*
 * command = ["<<", NULL]
 * type = HERE_DOC
 * */

typedef enum s_type
{
	WORD,
	PIPE,
	REDIR_IN,
	OUT,
	OUT_APPEND,
}	t_type;

typedef struct s_command
{
	char	**comm_arr;
	t_type	type;
}	t_command;

//command.c
t_command	*command_init(size_t size, t_type type);
void		command_free(void *command);

// commands.c
t_commands	*commands_append(t_commands **lst, t_command *comm);
void		commands_free(t_commands **lst);

// Executar(t_commands *commands)
// command1.next > command2.next > NULL

#endif
