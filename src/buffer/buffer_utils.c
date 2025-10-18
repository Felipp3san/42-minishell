/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:28:27 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 13:38:25 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

void	buffer_append_str(t_buffer *buffer, const char *str)
{
	if (!buffer || !str)
		return ;
	while (*str)
		buffer_append(buffer, *str++);
}
