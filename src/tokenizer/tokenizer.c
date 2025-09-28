/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 00:50:23 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"

void	free_tokenizer(t_tokenizer *tok)
{
	buffer_free(&tok->buffer);
	tokens_free(tok->tokens);
	free(tok->tokens);
}

static t_status	init_tokenizer(t_tokenizer *tok)
{
	tok->state = NORMAL;
	tok->quote_state = UNSET;
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

t_status	add_token(t_tokenizer *tok, t_quote quote)
{
	t_token	*token;
	char	*output;

	if (tok->buffer.size == 0)
		return (SUCCESS);
	if (buffer_flush(&tok->buffer, &output) != SUCCESS)
		return (ERR_MALLOC);
	token = token_create(output, quote);
	if (!token)
		return (free(output), ERR_MALLOC);
	if (tokens_append(tok->tokens, token) != SUCCESS)
	{
		free(token->value);
		free(token);
		return (free(output), ERR_MALLOC);
	}
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
			return (free_tokenizer(&tok), NULL);
		str++;
	}
	if (add_token(&tok, tok.quote_state) != SUCCESS)
		return (free_tokenizer(&tok), NULL);
	buffer_free(&tok.buffer);
	return (tok.tokens);
}
