/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:21:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 13:03:50 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "libft.h"
#include "utils.h"

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

void	print_parser_err(t_token *error)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	if (error->next == NULL)
		ft_putstr_fd("newline", 1);
	else
		ft_putstr_fd(error->value, 1);
	ft_putendl_fd("'", 1);
}

static size_t	size_without_quotes(const char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (!is_single_quote(str[i]) && !is_double_quote(str[i]))
			size++;
		i++;
	}
	return (size);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!str || !*str)
		return (NULL);
	size = size_without_quotes(str);
	new_str = (char *) malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_single_quote(str[i]) && !is_double_quote(str[i]))
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	should_expand_heredoc(char *value)
{
	return (!ft_strchr(value, '\"') && !ft_strchr(value, '\''));
}
