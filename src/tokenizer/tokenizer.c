/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 18:40:04 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"

t_status	add_token(t_buffer *buffer, t_list **out)
{
	t_list	*token;
	char	*output;

	if (buffer->size == 0)
		return (SUCCESS);
	output = buffer_flush(buffer);
	if (!output)
		return (ERR_MALLOC);
	token = ft_lstnew(output);
	if (!token)
	{
		free(output);
		return (ERR_MALLOC);
	}
	ft_lstadd_back(out, token);
	return (SUCCESS);
}

t_list	*tokenize(char const *str, t_list **out)
{
	t_tokenizer	tok;

	tok.state = NORMAL;
	tok.buffer = buffer_create();
	if (!tok.buffer)
		return (NULL);
	while (*str)
	{
		tok.ch = *str;
		if (tok.state == NORMAL)
			tok.err = normal_mode(&tok, out);
		else if (tok.state == SINGLE)
			tok.err = single_mode(&tok);
		else if (tok.state == DOUBLE)
			tok.err = double_mode(&tok);
		else if (tok.state == OPERATOR)
			tok.err = operator_mode(&tok, out);
		if (tok.err != SUCCESS)
			return (buffer_free(tok.buffer), NULL);
		str++;
	}
	if (add_token(tok.buffer, out) != SUCCESS)
		return (buffer_free(tok.buffer), NULL);
	buffer_free(tok.buffer);
	return (*out);
}
