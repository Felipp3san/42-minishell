/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 16:58:07 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 15:45:01 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft.h"
#include "types.h"
#include <unistd.h>

void print_buffer(t_buffer *buffer)
{
	ft_printf(CYAN"\n---------------------\n"RESET);
	ft_printf(CYAN"Buffer: \"%s\"\n", buffer->data ? buffer->data : "(null)"RESET);
	ft_printf(CYAN"Length: %u, Size: %u\n"RESET, buffer->capacity, buffer->size);
	ft_printf(CYAN"---------------------\n"RESET);
}

int	main(void)
{
	t_buffer	buffer;
	char		*output;

	/*========== Init test ==========*/
	if (buffer_init(&buffer) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"buffer_init failed.\n"RESET);
		return (1);
	}
	ft_printf(GREEN"\nBuffer initialized!\n"RESET);
	print_buffer(&buffer);

	/*========== Append test ==========*/
	if (buffer_append(&buffer, 'a') != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"buffer_append failed.\n"RESET);
		return (1);
	}
	if (buffer_append(&buffer, 'b') != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"buffer_append failed.\n"RESET);
		return (1);
	}
	if (buffer_append(&buffer, 'c') != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"buffer_append failed.\n"RESET);
		return (1);
	}
	ft_printf(GREEN"\nCharacters added in buffer!\n"RESET);
	print_buffer(&buffer);

	/*========== Flush/Reset test ==========*/
	output = buffer_flush(&buffer);
	if (!output)
	{
		ft_dprintf(STDERR_FILENO, RED"buffer_flush failed.\n"RESET);
		return (1);
	}
	ft_printf(GREEN"\nBuffer flushed. Output string: %s!\n"RESET, output);
	ft_printf(GREEN"\nBuffer reseted."RESET);
	print_buffer(&buffer);

	/*========== Free buffer ==========*/
	free(buffer.data);
	buffer.data = NULL;
	buffer.size = 0;
	buffer.capacity = 0;

	ft_printf(GREEN"\nBuffer freed."RESET);
	print_buffer(&buffer);

	free(output);
}
