/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 18:33:23 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "buffer.h"
#include "types.h"

t_status	add_token(t_token *tok, t_buffer *buffer)
{
	char	*output;

	if (!buffer->data && !*buffer->data)
		return (SUCCESS);
	if (buffer_flush(buffer, &output) != SUCCESS)
		return (ERR_MALLOC);
	tokens_append(tok, output);
	return (SUCCESS);
}

t_token	tokenizer(char const *str)
{
	t_token		token;
	t_buffer	buffer;

	tokenizer_init(&tok);
	if (buffer_init(&buffer) != SUCCESS)
		return (ERROR);
	if (tokens_init(shell) != SUCCESS)
		return (ERROR);
	while (*str)
	{
		if (tok.state == NORMAL)
			normal_mode(shell, &tok, *str);
		else if (tok.state == SINGLE)
			single_mode(&tok, *str);
		else if (tok.state == DOUBLE)
			double_mode(&tok, *str);
		else if (tok.state == OPERATOR)
			operator_mode(shell, &tok, *str);
		str++;
	}
	add_token(shell, &tok);
	free(tok.buffer);
	tok.buffer = NULL;
	return (SUCCESS);
}
