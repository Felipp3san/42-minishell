/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:14:21 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 21:28:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "types.h"

int	tokens_init(t_tokens *tok)
{
	tok->tokens = (char **) malloc(sizeof(char *) * 16);
	if (!tok->tokens)
		return (ERR_MALLOC);
	tok->tokens[0] = NULL;
	tok->size = 0;
	tok->capacity = 16;
	return (SUCCESS);
}

int	tokens_realloc(t_tokens *tok)
{
	char	**new_tokens;

	new_tokens = (char **) malloc(sizeof(char *) * (tok->capacity + 16));
	if (!new_tokens)
		return (ERR_MALLOC);
	ft_memcpy(new_tokens, tok->tokens, sizeof(char *) * (tok->size + 1));
	free(tok->tokens);
	tok->tokens = new_tokens;
	tok->capacity += 16;
	return (SUCCESS);
}

int	tokens_append(t_tokens *tok, const char *str)
{
	char	*token;

	if (tok->size + 1 >= tok->capacity)
	{
		if (tokens_realloc(tok) != SUCCESS)
			return (ERR_MALLOC);
	}
	token = ft_strdup(str);
	if (!token)
		return (ERR_MALLOC);
	tok->tokens[tok->size++] = token;
	tok->tokens[tok->size] = NULL;
	return (SUCCESS);
}

void	tokens_free(t_tokens *tok)
{
	size_t i;

	if (tok->tokens)
	{
		i = 0;
		while (tok->tokens[i])
			free(tok->tokens[i++]);
		free(tok->tokens);
	}
	tok->tokens = NULL;
	tok->size = 0;
	tok->capacity = 0;
}
