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
#include "libft.h"
#include "token.h"
//#include "minishell.h"
#include "types.h"

//void	free_tokenizer(t_tokenizer *tok)
//{
//	buffer_free(&tok->buffer);
//	tokens_free(tok->tokens);
//	free(tok->tokens);
//}

t_status	add_token(t_list **tokens, t_buffer *buffer)
{
	t_token	*token;
	t_list	*node;
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
	node = ft_lstnew((void *) token);
	if (!node)
	{
		free(output);
		free(token);
		return (ERR_MALLOC);
	}
	ft_lstadd_back(tokens, node);
	return (SUCCESS);
}

t_bool	has_open_quotes(const char *str)
{
	char	ch;
	t_state	mode;
	t_bool	single_opened;
	t_bool	double_opened;

	mode = NORMAL;
	single_opened = FALSE;
	double_opened = FALSE;
	while (*str)
	{
		ch = *str;
		if (is_single_quote(ch) && (mode != DOUBLE))
		{
			if (single_opened == TRUE)
			{
				mode = NORMAL;
				single_opened = FALSE;
			}
			else
			{
				mode = SINGLE;
				single_opened = TRUE;
			}
		}
		if (is_double_quote(ch) && (mode != SINGLE))
		{
			if (double_opened == TRUE)
			{
				mode = NORMAL;
				double_opened = FALSE;
			}
			else
			{
				mode = DOUBLE;
				double_opened = TRUE;
			}
		}
		str++;
	}
	return (single_opened || double_opened);
}

t_status	tokenizer(t_list **tokens, const char *str)
{
	t_buffer	buffer;
	t_state		state;
	char	ch;

	state = NORMAL;
	if (has_open_quotes(str))
		return (ERROR);
	if (!buffer_init(&buffer))
		return (ERR_MALLOC);
	while (*str)
	{
		ch = *str;
		if (state == NORMAL)
		{
			if (is_space(ch))
			{
				if (add_token(tokens, &buffer) != SUCCESS)
					return (ERR_MALLOC);
			}
			else if (is_single_quote(ch))
			{
				state = SINGLE;
				if (add_token(tokens, &buffer) != SUCCESS)
					return (ERR_MALLOC);
			}
			else if (is_double_quote(ch))
			{
				state = DOUBLE;
				if (add_token(tokens, &buffer) != SUCCESS)
					return (ERR_MALLOC);
			}
			else if (is_operator(ch))
			{
				state = OPERATOR;
				if (add_token(tokens, &buffer) != SUCCESS)
					return (ERR_MALLOC);
				if (!buffer_append(&buffer, ch))
					return (ERR_MALLOC);
			}
			else
			{
				if (!buffer_append(&buffer, ch))
					return (ERR_MALLOC);
			}
		}
		else if (state == SINGLE)
		{
			if (is_single_quote(ch))
			{
				state = NORMAL;
				if (add_token(tokens, &buffer) != SUCCESS)
					return (ERR_MALLOC);
			}
			else
			{
				if (!buffer_append(&buffer, ch))
					return (ERR_MALLOC);
			}
		}
		else if (state == DOUBLE)
		{
			if (is_double_quote(ch))
			{
				state = NORMAL;
				if (add_token(tokens, &buffer) != SUCCESS)
					return (ERR_MALLOC);
			}
			else
			{
				if (!buffer_append(&buffer, ch))
					return (ERR_MALLOC);
			}
		}
		else if (state == OPERATOR)
		{
			if (is_operator(ch) && ((ch == buffer.data[0]) && buffer.size < 2))
			{
				if (!buffer_append(&buffer, ch))
					return (ERR_MALLOC);
			}
			else
			{
				if (add_token(tokens, &buffer) != SUCCESS)
					return (ERR_MALLOC);
				state = NORMAL;
				str--;
				//normal_mode()
			}
		}
		str++;
	}
	if (add_token(tokens, &buffer) != SUCCESS)
		return (ERR_MALLOC);
	buffer_free(&buffer);
	return (SUCCESS);
}
