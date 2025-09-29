/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:34:11 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 01:01:41 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "tokens.h"
#include "libft.h"

void print_tokens(t_tokens *tok)
{
	size_t	i;
	char	*mode;

	ft_printf(CYAN"\n---------------------\n"RESET);
	ft_printf(CYAN"Tokens\n"RESET);
	i = 0;
	while (tok->tokens && tok->tokens[i])
	{
		ft_printf(CYAN"[%d] ", i);
		if (tok->tokens[i]->quote == NO_QUOTE)
			mode = "NO_QUOTE";
		else if (tok->tokens[i]->quote == SINGLE_QUOTE)
			mode = "SINGLE_QUOTE";
		else if (tok->tokens[i]->quote == SINGLE_QUOTE)
			mode = "DOUBLE_QUOTE";
		else
			mode = "UNSET";
		ft_printf(GREEN" MODE %s\t"RESET, mode);
		ft_printf(CYAN"%s\n"RESET, tok->tokens[i]->value);
		i++;
	}
	ft_printf(CYAN"Count: %u\n"RESET, tok->size);
	ft_printf(CYAN"---------------------\n"RESET);
}

int	main(void)
{
	t_tokens	tok;
	t_token		*token;

	/*========== Init test ==========*/
	if (tokens_init(&tok) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_init failed.\n"RESET);
		return (1);
	}
	ft_printf(GREEN"\nTokens initialized!\n"RESET);
	print_tokens(&tok);

	/*========== Append test ==========*/
	token = token_create("echo", NO_QUOTE, FALSE);
	if (!token)
		return (1);
	if (tokens_append(&tok, token) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		free(token);
		return (1);
	}

	token = token_create("Hello world", DOUBLE_QUOTE, TRUE);
	if (!token)
		return (1);
	if (tokens_append(&tok, token) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		free(token);
		return (1);
	}

	token = token_create(">>", NO_QUOTE, TRUE);
	if (!token)
		return (1);
	if (tokens_append(&tok, token) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		return (1);
	}

	token = token_create("output.txt", SINGLE_QUOTE, FALSE);
	if (!token)
		return (1);
	if (tokens_append(&tok, token) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		return (1);
	}

	ft_printf(GREEN"\nTokens added in the array!\n"RESET);
	print_tokens(&tok);

	/*========== Free tokens ==========*/
	tokens_free(&tok);
	ft_printf(GREEN"\nTokens freed.\n"RESET);
	print_tokens(&tok);

	return (0);
}
