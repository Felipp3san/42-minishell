/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:07:06 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 18:18:34 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_internal.h"

t_bool	is_word(t_type type)
{
	return (type == WORD);
}

t_bool	is_redir(t_type type)
{
	return (type == INPUT || type == OUTPUT || type == APPEND
		|| type == HEREDOC);
}

t_type	get_token_type(char *str)
{
	char	*value;

	value = (char *) str;
	if (ft_strcmp(value, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(value, ">") == 0)
		return (OUTPUT);
	else if (ft_strcmp(value, ">>") == 0)
		return (APPEND);
	else if (ft_strcmp(value, "<") == 0)
		return (INPUT);
	else if (ft_strcmp(value, "<<") == 0)
		return (HEREDOC);
	else
		return (WORD);
}

void	move_forward(t_list **start, size_t count)
{
	while (*start && count > 0)
	{
		(*start) = (*start)->next;
		count--;
	}
}
