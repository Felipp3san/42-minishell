/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:21:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/10 13:40:01 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "libft.h"

void	print_parser_err(t_token *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	if (error->next == NULL)
		ft_putstr_fd("newline", 1);
	else
		ft_putstr_fd(error->value, 1);
	ft_putendl_fd("'", 1);
}

t_bool	is_redir(t_token_type type)
{
	return (type == OUTPUT || type == INPUT || type == APPEND 
		|| type == HEREDOC);
}

t_bool	is_sep(t_token_type type)
{
	return (type == OUTPUT || type == INPUT || type == APPEND 
		|| type == HEREDOC || type == PIPE);
}

t_bool	is_word(t_token_type type)
{
	return (type == WORD);
}

t_bool	is_heredoc(t_token_type type)
{
	return (type == HEREDOC);
}
