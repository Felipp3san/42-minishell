/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:03:25 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 13:28:19 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "buffer.h"
#include "libft.h"

t_buffer	*buffer_create(t_buffer **buf)
{
	t_buffer	*buffer;

	if (buf)
	{
		*buf = (t_buffer *) malloc(sizeof(t_buffer));
		buffer = *buf;
	}
	else
		buffer = (t_buffer *) malloc(sizeof(t_buffer));
	if (!buffer)
		return (NULL);
	buffer->data = (char *) malloc(16);
	if (!buffer->data)
	{
		free(buffer);
		return (NULL);
	}
	buffer->size = 0;
	buffer->capacity = 16;
	buffer->data[0] = '\0';
	return (buffer);
}

t_buffer	*buffer_realloc(t_buffer *buffer)
{
	char	*new_buffer;

	new_buffer = (char *) malloc(buffer->capacity + 16);
	if (!new_buffer)
		return (NULL);
	ft_memcpy(new_buffer, buffer->data, buffer->size + 1);
	free(buffer->data);
	buffer->data = new_buffer;
	buffer->capacity += 16;
	return (buffer);
}

t_buffer	*buffer_append(t_buffer *buffer, char ch)
{
	if (buffer->size + 1 >= buffer->capacity)
	{
		if (!buffer_realloc(buffer))
			return (NULL);
	}
	buffer->data[buffer->size++] = ch;
	buffer->data[buffer->size] = '\0';
	return (buffer);
}

char	*buffer_flush(t_buffer *buffer)
{
	char	*output;

	if (buffer->size == 0)
		return (NULL);
	output = ft_strdup(buffer->data);
	if (!output)
		return (NULL);
	buffer->size = 0;
	buffer->data[0] = '\0';
	return (output);
}

void	buffer_free(t_buffer *buffer)
{
	if (!buffer)
		return ;
	if (buffer->data)
		free(buffer->data);
	free(buffer);
}
