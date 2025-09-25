/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 12:07:34 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	tokenizer_init(t_tokenizer *tok)
{
	tok->buffer = NULL;
	tok->output = NULL;
	tok->buf_len = 0;
	tok->state = NORMAL;
}

void	add_token(t_shell *shell, t_tokenizer *tok)
{
	if (buffer_flush(tok) != SUCCESS)
	{
		free(tok->buffer);
		free_exit(shell);
	}
	tokens_append(shell, tok->output);
	tok->output = NULL;
}

int	tokenizer(char const *str, t_shell *shell)
{
	t_tokenizer	tok;

	tokenizer_init(&tok);
	if (tokens_init(shell) != SUCCESS)
		return (ERROR);
	if (buffer_init(&tok) != SUCCESS)
		return (ERROR);
	while (*str)
	{
		if (tok.state == NORMAL)
			normal_mode(shell, &tok, *str);
		else if (tok.state == SINGLE)
			single_mode(&tok, *str);
		else if (tok.state == DOUBLE)
			double_mode(&tok, *str);
		else if (tok.state == OPERATOR)
			operator_mode(shell, &tok, *str);
		str++;
	}
	add_token(shell, &tok);
	free(tok.buffer);
	return (SUCCESS);
}
