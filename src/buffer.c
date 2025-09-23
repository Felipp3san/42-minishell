/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:03:25 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/23 18:17:56 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include "libft.h"

void	reset_buffer(char **buffer, size_t *buf_len)
{
	if (!buffer || !*buffer)
		return ;
	*buffer[0] = '\0';
	(*buf_len) = 0;
}

int	buffer_init(char **buffer)
{
	*buffer = (char *) malloc(sizeof(char) + 1);
	if (!*buffer)
		return (ERR_MALLOC);
	**buffer = '\0';
	return (SUCCESS);
}

int	buffer_flush(char **buffer, size_t *buf_len, t_shell *shell)
{
	char	**new_tokens;
	
	if (*buf_len > 0)
	{
		new_tokens = (char **) malloc(sizeof(char *) * (shell->token_count + 2));
		if (!new_tokens)
			return (ERR_MALLOC);
		ft_memcpy(new_tokens, shell->tokens, sizeof(char *) * shell->token_count);
		new_tokens[shell->token_count] = ft_strdup(*buffer);
		new_tokens[shell->token_count + 1] = NULL;
		free(shell->tokens);
		shell->tokens = new_tokens;
		shell->token_count++;
	}
	reset_buffer(buffer, buf_len);
	return (SUCCESS);
}

int	buffer_append(char **buffer, size_t *buf_len, char ch)
{
	char	*new_buffer;

	new_buffer = (char *) malloc(sizeof(char *) * (*buf_len + 2));
	if (!new_buffer)
		return (ERR_MALLOC);
	ft_memcpy(new_buffer, *buffer, *buf_len);
	free(*buffer);
	new_buffer[*buf_len] = ch;
	new_buffer[*buf_len + 1] = '\0';
	*buffer = new_buffer;
	(*buf_len)++;
	return (SUCCESS);
}
