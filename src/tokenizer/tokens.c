/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:22:20 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 18:56:41 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "types.h"

int	tokens_init(t_token *tok)
{
	tok->tokens = (char **) malloc(sizeof(char *));
	if (!tok->tokens)
		return (ERR_MALLOC);
	tok->tokens[0] = NULL;
	tok->count = 0;
	return (SUCCESS);
}

int	realloc_tokens(t_token *tok)
{
	char	**new_tokens;

	new_tokens = (char **) malloc(sizeof(char *) * (tok->count + 2));
	if (!new_tokens)
		return (ERR_MALLOC);
	ft_memcpy(new_tokens, tok->tokens, sizeof(char *) * tok->count);
	free(tok->tokens);
	tok->tokens = new_tokens;
	tok->count++;
	return (SUCCESS);
}

int	tokens_append(t_token *tok, char *str)
{
	if (!str)
		return (SUCCESS);
	if (realloc_tokens(tok) != SUCCESS)
		return (ERR_MALLOC);
	tok->tokens[tok->count - 1] = str;
	tok->tokens[tok->count] = NULL;
	return (SUCCESS);
}

void	free_tokens(t_token *tok)
{
	size_t i;

	if (!tok->tokens || !*tok->tokens)
		return ;
	i = 0;
	while (tok->tokens[i])
	{
		free(tok->tokens[i]);
		tok->tokens[i++] = NULL;
	}
	free(tok->tokens);
	tok->tokens = NULL;
	tok->count = 0;
}
