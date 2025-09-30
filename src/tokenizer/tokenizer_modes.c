/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_modes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:43:15 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 14:06:15 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "buffer.h"
#include "tokenizer.h"

int	flush_and_set_state(t_tokenizer *tok, t_tokens **tokens, t_state new_state)
{
	tok->state = new_state;
	return (add_token(tokens, &tok->buffer));
}

int	normal_mode(t_tokenizer *tok, t_tokens **tokens)
{
	if (is_space(tok->ch))
		return (flush_and_set_state(tok, tokens, NORMAL));
	else if (is_single_quote(tok->ch))
		tok->state = SINGLE;
	else if (is_double_quote(tok->ch))
		tok->state = DOUBLE;
	else if (is_operator(tok->ch))
	{
		if (flush_and_set_state(tok, tokens, OPERATOR) != SUCCESS)
			return (ERR_MALLOC);
		if (!buffer_append(&tok->buffer, tok->ch))
			return (ERR_MALLOC);
	}
	else
	{
		if (!buffer_append(&tok->buffer, tok->ch))
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	single_mode(t_tokenizer *tok, t_tokens **tokens)
{
	if (is_single_quote(tok->ch))
		return (flush_and_set_state(tok, tokens, NORMAL));
	else
	{
		if (tok->ch == '$')
			tok->ch = 31;
		if (!buffer_append(&tok->buffer, tok->ch))
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	double_mode(t_tokenizer *tok, t_tokens **tokens)
{
	if (is_double_quote(tok->ch))
		return (flush_and_set_state(tok, tokens, DOUBLE));
	else
	{
		if (!buffer_append(&tok->buffer, tok->ch))
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	operator_mode(t_tokenizer *tok, t_tokens **tokens)
{
	t_buffer	*buffer;

	buffer = &tok->buffer;
	if (is_operator(tok->ch)
		&& ((tok->ch == buffer->data[0]) && buffer->size < 2))
	{
		if (!buffer_append(buffer, tok->ch))
			return (ERR_MALLOC);
	}
	else
	{
		if (flush_and_set_state(tok, tokens, NORMAL) != SUCCESS)
			return (ERR_MALLOC);
		normal_mode(tok, tokens);
	}
	return (SUCCESS);
}
