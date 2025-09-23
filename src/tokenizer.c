/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/23 18:26:00 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	free_tokens(t_shell *shell) 
{
	size_t i;

	i = 0;
	while (shell->tokens[i])
		free(shell->tokens[i++]);
	free(shell->tokens);
	shell->tokens = NULL;
	shell->token_count = 0;
}

int	init_tokens(t_shell *shell)
{
	shell->tokens = (char **) malloc(sizeof(char *));
	if (!shell->tokens)
		return (ERR_MALLOC);
	*shell->tokens = NULL;
	return (SUCCESS);
}

void	print_tokens(char **tokens)
{
	while (*tokens)
	{
		ft_printf("%s\n", *tokens);
		tokens++;
	}
}

int	tokenizer(const char *str, t_shell *shell)
{
	char	*buffer;
	size_t	buf_len;
	t_state	state;

	buffer = NULL;
	buf_len = 0;
	state = NORMAL;
	init_tokens(shell);
	buffer_init(&buffer);
	while (*str)
	{
		if (state == NORMAL)
		{
			if (*str == ' ')
				buffer_flush(&buffer, &buf_len, shell);
			else if (*str == '\'')
				state = SINGLE;
			else if (*str == '\"')
				state = DOUBLE;
			else
				buffer_append(&buffer, &buf_len, *str);
		}
		else if (state == SINGLE)
		{
			if (*str == '\'')
				state = NORMAL;
			else
				buffer_append(&buffer, &buf_len, *str);
		}
		else if (state == DOUBLE)
		{
			if (*str == '\"')
				state = NORMAL;
			else
				buffer_append(&buffer, &buf_len, *str);
		}
		str++;
	}
	buffer_flush(&buffer, &buf_len, shell);
	free(buffer);
	return (SUCCESS);
}
