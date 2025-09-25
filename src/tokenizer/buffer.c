/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:03:25 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 18:27:03 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "buffer.h"
#include "libft.h"
#include "types.h"

int	buffer_init(t_buffer *buffer)
{
	buffer->data = (char *) malloc(sizeof(char));
	if (!buffer->data)
		return (ERR_MALLOC);
	buffer->data[0] = '\0';
	buffer->len = 0;
	buffer->size = 0;
	return (SUCCESS);
}

int	realloc_buffer(t_buffer *buffer)
{
	char	*new_buffer;

	new_buffer = (char *) malloc(buffer->size + 2);
	if (!new_buffer)
		return (ERR_MALLOC);
	ft_memcpy(new_buffer, buffer->data, buffer->size);
	free(buffer->data);
	buffer->data = new_buffer;
	buffer->size++;
	return (SUCCESS);
}

int	buffer_append(t_buffer *buffer, char ch)
{
	if (buffer->len >= buffer->size)
	{
		if (realloc_buffer(buffer) != SUCCESS)
			return (ERR_MALLOC);
	}
	buffer->data[buffer->len++] = ch;
	buffer->data[buffer->len] = '\0';
	return (SUCCESS);
}

int	buffer_flush(t_buffer *buffer, char **output)
{
	if (buffer->len == 0)
		return (SUCCESS);
	*output = ft_strdup(buffer->data);
	if (!*output)
		return (ERR_MALLOC);
	buffer_reset(buffer);
	return (SUCCESS);
}

void	buffer_reset(t_buffer *buffer)
{
	if (!buffer->data)
		return ;
	buffer->data[0] = '\0';
	buffer->len = 0;
}
