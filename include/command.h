/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:16:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/10 13:37:55 by fde-alme         ###   ########.fr       */
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
	struct s_redir		*next;
	struct s_redir		*previous;
}	t_redir;

typedef struct s_command
{
	char				**argv;
	size_t				size;
	size_t				capacity;
	t_redir				*redirs;
	struct s_command	*next;
	struct s_command	*previous;
}	t_command;

#endif
