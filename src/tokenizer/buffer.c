/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:03:25 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 13:11:38 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include "libft.h"

void	buffer_reset(t_tokenizer *tok)
{
	if (!tok->buffer)
		return ;
	tok->buffer[0] = '\0';
	tok->buf_len = 0;
}

int	buffer_init(t_tokenizer *tok)
{
	tok->buffer = (char *) malloc(sizeof(char));
	if (!tok->buffer)
		return (ERR_MALLOC);
	tok->buffer[0] = '\0';
	return (SUCCESS);
}

int	buffer_flush(t_tokenizer *tok)
{
	if (tok->buf_len == 0)
	{
		tok->output = NULL;
		return (SUCCESS);
	}
	tok->output = ft_strdup(tok->buffer);
	if (!tok->output)
		return (ERR_MALLOC);
	buffer_reset(tok);
	return (SUCCESS);
}

int	buffer_append(t_tokenizer *tok, char ch)
{
	char	*new_buffer;

	new_buffer = (char *) malloc(tok->buf_len + 2);
	if (!new_buffer)
		return (ERR_MALLOC);
	ft_memcpy(new_buffer, tok->buffer, tok->buf_len);
	new_buffer[tok->buf_len] = ch;
	new_buffer[tok->buf_len + 1] = '\0';
	free(tok->buffer);
	tok->buffer = new_buffer;
	tok->buf_len++;
	return (SUCCESS);
}
