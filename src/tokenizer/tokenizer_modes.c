/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_modes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:43:15 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 12:20:04 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * If state is set to NORMAL mode, it should add every char to the buffer until
 * a space is found, if space is found, flush the buffer. If any other mode is 
 * found, just switch state to the new mode.
 * */
void	normal_mode(t_shell *shell, t_tokenizer *tok, char ch)
{
	if (is_space(ch))
		add_token(shell, tok);
	else if (is_operator(ch))
	{
		add_token(shell, tok);
		buffer_append(tok, ch);
		tok->state = OPERATOR;
	}
	else if (is_single_quote(ch))
		tok->state = SINGLE;
	else if (is_double_quote(ch))
		tok->state = DOUBLE;
	else
		buffer_append(tok, ch);
}

/*
 * If state is set to SINGLE mode it should add every char to the buffer until
 * another single quote is found, when it happens, state is set back to NORMAL.
 * */
void	single_mode(t_tokenizer *tok, char ch)
{
	if (is_single_quote(ch))
		tok->state = NORMAL;
	else
		buffer_append(tok, ch);
}

/*
 * If state is set to DOUBLE mode it should add every char to the buffer until
 * another double quote is found, when it happens, state is set back to NORMAL.
 * */
void	double_mode(t_tokenizer *tok, char ch)
{
	if (is_double_quote(ch))
		tok->state = NORMAL;
	else
		buffer_append(tok, ch);
}

/*
 * If state is set to OPERATOR mode, it should look if the next is an operator 
 * of the same type. If not, just flush buff and set the mode back to NORMAL.
 */
void	operator_mode(t_shell *shell, t_tokenizer *tok, char ch)
{
	if (is_operator(ch))
	{
		if (tok->buffer && (tok->buffer[0] == ch))
			buffer_append(tok, ch);
		else
		{
			add_token(shell, tok);
			buffer_append(tok, ch);
		}
	}
	else
	{
		add_token(shell, tok);
		tok->state = NORMAL;
		normal_mode(shell, tok, ch);
	}
}
