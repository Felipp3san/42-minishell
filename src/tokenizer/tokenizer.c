/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/29 17:14:43 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tokenizer.h"
#include "token.h"
#include "types.h"

t_status	add_token(t_tokens **tokens, t_buffer *buffer)
{
	t_token	*token;
	char	*output;

	if (buffer->size == 0)
		return (SUCCESS);
	output = buffer_flush(buffer);
	if (!output)
		return (ERR_MALLOC);
	token = token_new(output);
	if (!token)
	{
		free(output);
		return (ERR_MALLOC);
	}
	if (!token_append(tokens, token))
	{
		token_free(token);
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

t_status	tokenize(char const *str, t_tokens **out)
{
	t_tokenizer	tok;

	tok.state = NORMAL;
	if (!buffer_init(&tok.buffer))
		return (ERR_MALLOC);
	while (*str)
	{
		tok.ch = *str;
		if (tok.state == NORMAL)
			normal_mode(&tok, out);
		else if (tok.state == SINGLE)
			single_mode(&tok, out);
		else if (tok.state == DOUBLE)
			double_mode(&tok, out);
		else if (tok.state == OPERATOR)
			operator_mode(&tok, out);
		str++;
	}
	if (add_token(out, &tok.buffer) != SUCCESS)
		return (ERR_MALLOC);
	buffer_free(&tok.buffer);
	return (SUCCESS);
}
