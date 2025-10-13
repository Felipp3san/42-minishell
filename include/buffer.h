/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:00:19 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 19:16:54 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <stddef.h>

typedef struct s_buffer
{
	char	*data;
	size_t	size;
	size_t	capacity;
}	t_buffer;

t_buffer	*buffer_create(t_buffer **buf);
t_buffer	*buffer_realloc(t_buffer *buffer);
t_buffer	*buffer_append(t_buffer *buffer, char ch);
char		*buffer_flush(t_buffer *buffer);
void		buffer_free(t_buffer *buffer);

#endif
