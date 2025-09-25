/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:00:19 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 18:26:59 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

#include <stddef.h>

typedef struct s_buffer
{
	char	*data;
	size_t	len;
	size_t	size;
}	t_buffer;

void	buffer_reset(t_buffer *buffer);
int		buffer_init(t_buffer *buffer);
int		buffer_flush(t_buffer *buffer, char **output);
int		realloc_buffer(t_buffer *buffer);
int		buffer_append(t_buffer *buffer, char ch);

#endif
