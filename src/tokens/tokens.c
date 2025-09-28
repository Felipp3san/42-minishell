/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:14:21 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 00:35:21 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"
#include "types.h"

int	tokens_init(t_tokens *tok)
{
	tok->tokens = (t_token **) malloc(sizeof(t_token *) * 16);
	if (!tok->tokens)
		return (ERR_MALLOC);
	tok->tokens[0] = NULL;
	tok->size = 0;
	tok->capacity = 16;
	return (SUCCESS);
}

int	tokens_realloc(t_tokens *tok)
{
	t_token	**new_tokens;

	new_tokens = (t_token **) malloc(sizeof(t_token *) * (tok->capacity + 16));
	if (!new_tokens)
		return (ERR_MALLOC);
	ft_memcpy(new_tokens, tok->tokens, sizeof(t_token *) * (tok->size + 1));
	free(tok->tokens);
	tok->tokens = new_tokens;
	tok->capacity += 16;
	return (SUCCESS);
}

int	tokens_append(t_tokens *tokens, t_token *token)
{
	if (!token)
		return (SUCCESS);
	if (tokens->size + 1 >= tokens->capacity)
	{
		if (tokens_realloc(tokens) != SUCCESS)
			return (ERR_MALLOC);
	}
	tokens->tokens[tokens->size++] = token;
	tokens->tokens[tokens->size] = NULL;
	return (SUCCESS);
}

void	tokens_free(t_tokens *tok)
{
	size_t	i;

	if (tok->tokens)
	{
		i = 0;
		while (tok->tokens[i])
		{
			free(tok->tokens[i]->value);
			free(tok->tokens[i++]);
		}
		free(tok->tokens);
	}
	tok->tokens = NULL;
	tok->size = 0;
	tok->capacity = 0;
}
