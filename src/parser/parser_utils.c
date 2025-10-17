/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:21:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:40:24 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "utils.h"
#include "libft.h"

t_token	*syntax_check(t_token *token)
{
	if (token->type == PIPE)
		return (token);
	while (token)
	{
		if (!token->next && is_sep(token->type))
			break ;
		if (is_redir(token->type) && is_sep(token->next->type))
			break ;
		if (token->type == PIPE && token->next->type == PIPE)
			break ;
		token = token->next;
	}
	return (token);
}

char	*get_redir_value(char *token_value, int *expand)
{
	if (ft_strchr(token_value, '\"') || ft_strchr(token_value, '\''))
	{
		*expand = FALSE;
		return (remove_quotes(token_value));
	}
	*expand = TRUE;
	return (ft_strdup(token_value));
}

void	print_parser_err(t_token *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	if (error->next == NULL)
		ft_putstr_fd("newline", 1);
	else
		ft_putstr_fd(error->value, 1);
	ft_putendl_fd("'", 1);
}
