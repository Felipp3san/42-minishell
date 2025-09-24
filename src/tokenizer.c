/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/24 15:40:01 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	tokenizer(char const *str, t_shell *shell)
{
	t_tokenizer	tok;
	char		*output;

	tok.buffer = NULL;
	tok.buf_len = 0;
	tok.state = NORMAL;

	if (tokens_init(shell) != SUCCESS)
		return (ERROR);
	if (buffer_init(&tok) != SUCCESS)
		return (ERROR);
	while (*str)
	{
		if (tok.state == NORMAL)
		{
			if (*str == ' ')
			{
				if (buffer_flush(&tok, &output) != SUCCESS)
				{
					free(tok.buffer);
					free_exit(shell);
				}
				tokens_append(shell, output);
			}
			else if (*str == '\'')
				tok.state = SINGLE;
			else if (*str == '\"')
				tok.state = DOUBLE;
			else
				buffer_append(&tok, *str);
		}
		else if (tok.state == SINGLE)
		{
			if (*str == '\'')
				tok.state = NORMAL;
			else
				buffer_append(&tok, *str);
		}
		else if (tok.state == DOUBLE)
		{
			if (*str == '\"')
				tok.state = NORMAL;
			else
				buffer_append(&tok, *str);
		}
		str++;
	}
	if (buffer_flush(&tok, &output) != SUCCESS)
	{
		free(tok.buffer);
		free_exit(shell);
	}
	tokens_append(shell, output);
	free(tok.buffer);
	return (SUCCESS);
}
