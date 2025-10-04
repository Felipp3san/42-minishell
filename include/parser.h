/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:02:39 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 19:01:38 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"

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

t_list	*parse(t_list *tokens, t_list **out);
void	free_command(void *content);

#endif
