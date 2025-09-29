/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_modes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:43:15 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 01:22:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "buffer.h"
#include "tokenizer.h"

static int	flush_and_set_state(t_list **tokens, t_buffer *buffer, t_state *state, t_state new_state)
{
	*state = new_state;
	return (!add_token(tokens, buffer));
}

int	normal_mode(t_list **tokens, t_buffer *buffer, t_state *state, char ch)
{
	if (is_space(ch))
		return (flush_and_set_state(tokens, buffer, state, NORMAL));
	else if (is_single_quote(ch))
		return (flush_and_set_state(tokens, buffer, state, SINGLE));
	else if (is_double_quote(ch))
		return (flush_and_set_state(tokens, buffer, state, DOUBLE));
	else if (is_operator(ch))
	{
		return (flush_and_set_state(tokens, buffer, state, OPERATOR));
		if (!buffer_append(buffer, ch))
			return (ERR_MALLOC);
	}
	else
		return (!buffer_append(buffer, ch));
}

int	single_mode(t_list **tokens, t_buffer *buffer, t_state *state, char ch)
{
	if (is_single_quote(ch))
		return (flush_and_set_state(tokens, buffer, state, NORMAL));
	else
		return (!buffer_append(buffer, ch));
}

int	double_mode(t_list **tokens, t_buffer *buffer, t_state *state, char ch)
{
	if (is_double_quote(ch))
		return (flush_and_set_state(tokens, buffer, state, DOUBLE));
	else
		return (!buffer_append(buffer, ch));
}

int	operator_mode(t_list **tokens, t_buffer *buffer, t_state *state, char ch)
{
	if (is_operator(ch) && ((ch == buffer->data[0]) && buffer->size < 2))
	{
		if (!buffer_append(buffer, ch))
			return (ERR_MALLOC);
	}
	else
	{
		if (flush_and_set_state(tokens, buffer, state, NORMAL) != SUCCESS)
			return (ERR_MALLOC);
		normal_mode(tokens, buffer, state, ch);
	}
	return (SUCCESS);
}
