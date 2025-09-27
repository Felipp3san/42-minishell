/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_modes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:43:15 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 22:39:11 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "types.h"

/* 
 * If state is set to NORMAL mode, it should add every char to the buffer until
 * a space is found, if space is found, flush the buffer. If any other mode is 
 * found, just switch state to the new mode.
 * */
t_status	normal_mode(t_tokenizer *tok, char ch)
{
	if (is_space(ch))
		return (add_token(tok));
	else if (is_operator(ch))
	{
		tok->state = OPERATOR;
		return (buffer_append(&tok->buffer, ch));
	}
	else if (is_single_quote(ch))
		tok->state = SINGLE;
	else if (is_double_quote(ch))
		tok->state = DOUBLE;
	else
		return (buffer_append(&tok->buffer, ch));
	return (SUCCESS);
}

/*
 * If state is set to SINGLE mode it should add every char to the buffer until
 * another single quote is found, when it happens, state is set back to NORMAL.
 * */
t_status	single_mode(t_tokenizer *tok, char ch)
{
	if (is_single_quote(ch))
		tok->state = NORMAL;
	else
		return (buffer_append(&tok->buffer, ch));
	return (SUCCESS);
}

/*
 * If state is set to DOUBLE mode it should add every char to the buffer until
 * another double quote is found, when it happens, state is set back to NORMAL.
 * */
t_status	double_mode(t_tokenizer *tok, char ch)
{
	if (is_double_quote(ch))
	{
		tok->state = NORMAL;
		return (SUCCESS);
	}
	else
		return (buffer_append(&tok->buffer, ch));
}

/*
 * If state is set to OPERATOR mode, it should look if the next is an operator 
 * of the same type. If not, just flush buff and set the mode back to NORMAL.
 */
t_status	operator_mode(t_tokenizer *tok, char ch)
{
	if (is_operator(ch))
	{
		if ((tok->buffer.size > 0 && tok->buffer.size < 2)
			&& (tok->buffer.data[0] == ch))
			return (buffer_append(&tok->buffer, ch));
		else
		{
			if (add_token(tok) != SUCCESS)
				return (ERR_MALLOC);
			return (buffer_append(&tok->buffer, ch));
		}
	}
	else
	{
		if (add_token(tok) != SUCCESS)
			return (ERR_MALLOC);
		tok->state = NORMAL;
		return (normal_mode(tok, ch));
	}
}
