/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:03:25 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 22:38:35 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "buffer.h"
#include "libft.h"
#include "types.h"

int	buffer_init(t_buffer *buffer)
{
	buffer->data = (char *) malloc(16);
	if (!buffer->data)
		return (ERR_MALLOC);
	buffer->size = 0;
	buffer->capacity = 16;
	buffer->data[0] = '\0';
	return (SUCCESS);
}

int	buffer_realloc(t_buffer *buffer)
{
	char	*new_buffer;

	new_buffer = (char *) malloc(buffer->capacity + 16);
	if (!new_buffer)
		return (ERR_MALLOC);
	ft_memcpy(new_buffer, buffer->data, buffer->size + 1);
	free(buffer->data);
	buffer->data = new_buffer;
	buffer->capacity += 16;
	return (SUCCESS);
}

int	buffer_append(t_buffer *buffer, char ch)
{
	if (buffer->size + 1 >= buffer->capacity)
	{
		if (buffer_realloc(buffer) != SUCCESS)
			return (ERR_MALLOC);
	}
	buffer->data[buffer->size++] = ch;
	buffer->data[buffer->size] = '\0';
	return (SUCCESS);
}

int	buffer_flush(t_buffer *buffer, char **output)
{
	if (buffer->size == 0)
	{
		output = NULL;
		return (SUCCESS);
	}
	*output = ft_strdup(buffer->data);
	if (!*output)
		return (ERR_MALLOC);
	buffer->size = 0;
	buffer->data[0] = '\0';
	return (SUCCESS);
}

void	buffer_free(t_buffer *buffer)
{
	if (buffer->data)
		free(buffer->data);
	buffer->data = NULL;
	buffer->size = 0;
	buffer->capacity = 0;
}
