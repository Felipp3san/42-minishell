/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 22:07:57 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"

void	free_all(t_tokenizer *tok)
{
	buffer_free(&tok->buffer);
	tokens_free(tok->tokens);
	free(tok->tokens);
}

static t_status	init_tokenizer(t_tokenizer *tok)
{
	tok->state = NORMAL;
	tok->tokens = (t_tokens *) malloc(sizeof(t_tokens));
	if (!tok->tokens)
		return (ERR_MALLOC);
	if (buffer_init(&tok->buffer) != SUCCESS)
	{
		free(tok->tokens);
		return (ERR_MALLOC);
	}
	if (tokens_init(tok->tokens) != SUCCESS)
	{
		free(tok->tokens);
		buffer_free(&tok->buffer);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

t_status	add_token(t_tokenizer *tok)
{
	char	*output;

	if (tok->buffer.size == 0)
		return (SUCCESS);
	if (buffer_flush(&tok->buffer, &output) != SUCCESS)
		return (ERR_MALLOC);
	if (tokens_append(tok->tokens, output) != SUCCESS)
		return (free(output), ERR_MALLOC);
	free(output);
	return (SUCCESS);
}

t_tokens	*tokenizer(char const *str)
{
	t_tokenizer	tok;
	t_status	err;

	if (init_tokenizer(&tok) != SUCCESS)
		return (NULL);
	while (*str)
	{
		if (tok.state == NORMAL)
			err = normal_mode(&tok, *str);
		else if (tok.state == SINGLE)
			err = single_mode(&tok, *str);
		else if (tok.state == DOUBLE)
			err = double_mode(&tok, *str);
		else if (tok.state == OPERATOR)
			err = operator_mode(&tok, *str);
		if (err != SUCCESS)
			return (free_all(&tok), NULL);
		str++;
	}
	if (add_token(&tok) != SUCCESS)
		return (free_all(&tok), NULL);
	buffer_free(&tok.buffer);
	return (tok.tokens);
}
