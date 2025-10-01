/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:02:39 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 14:39:21 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"

typedef enum s_type
{
	WORD,
	UNSET,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC,
}	t_type;

typedef struct s_redir
{
	t_type	type;
	char	*filename;
}	t_redir;

typedef struct s_command
{
	char	**argv;
	t_list	*redirs;
}	t_command;

int	parser(t_list *tokens, t_list **out);

#endif
