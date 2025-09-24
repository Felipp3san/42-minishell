/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:22:20 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/24 15:32:41 by fde-alme         ###   ########.fr       */
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

int	tokens_init(t_shell *shell)
{
	shell->tokens = (char **) malloc(sizeof(char *));
	if (!shell->tokens)
		return (ERR_MALLOC);
	shell->tokens[0] = NULL;
	return (SUCCESS);
}

int	tokens_append(t_shell *shell, char *str)
{
	char	**new_tokens;
	
	if (!str)
		return (SUCCESS);
	new_tokens = (char **) malloc(sizeof(char *) * (shell->token_count + 2));
	if (!new_tokens)
		return (ERR_MALLOC);
	ft_memcpy(new_tokens, shell->tokens, sizeof(char *) * shell->token_count);
	new_tokens[shell->token_count] = str;
	new_tokens[shell->token_count + 1] = NULL;
	free(shell->tokens);
	shell->tokens = new_tokens;
	shell->token_count++;
	return (SUCCESS);
}

void	tokens_print(char **tokens)
{
	while (*tokens)
	{
		ft_printf("%s\n", *tokens);
		tokens++;
	}
}
