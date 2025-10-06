/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 14:24:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/05 14:25:30 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stddef.h>
# include "libft.h"

typedef enum s_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_type;

typedef struct s_redir
{
	char	*filename;
	t_type	type;
}	t_redir;

typedef struct s_command
{
	char	**argv;
	size_t	size;
	size_t	capacity;
	t_list	*redirs;
}	t_command;

#endif
