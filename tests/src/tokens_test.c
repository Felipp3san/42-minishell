/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:34:11 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 20:22:41 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "token.h"
#include "libft.h"

void print_tokens(t_tokens *tok)
{
	size_t	i;

	ft_printf(CYAN"\n---------------------\n"RESET);
	ft_printf(CYAN"Tokens\n"RESET);
	i = 0;
	while (tok->tokens && tok->tokens[i])
	{
		ft_printf(CYAN"[%d] - %s\n"RESET, i, tok->tokens[i]);
		i++;
	}
	ft_printf(CYAN"Count: %u\n"RESET, tok->size);
	ft_printf(CYAN"---------------------\n"RESET);
}

int	main(void)
{
	t_tokens	tok;

	/*========== Init test ==========*/
	if (tokens_init(&tok) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_init failed.\n"RESET);
		return (1);
	}
	ft_printf(GREEN"\nTokens initialized!\n"RESET);
	print_tokens(&tok);

	/*========== Append test ==========*/
	if (tokens_append(&tok, "echo") != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		return (1);
	}
	if (tokens_append(&tok, "Hello world") != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		return (1);
	}
	if (tokens_append(&tok, ">>") != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		return (1);
	}
	if (tokens_append(&tok, "output.txt") != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, RED"tokens_append failed.\n"RESET);
		return (1);
	}
	ft_printf(GREEN"\nTokens added in the array!\n"RESET);
	print_tokens(&tok);

	/*========== Free tokens ==========*/
	tokens_free(&tok);
	ft_printf(GREEN"\nTokens freed."RESET);
	print_tokens(&tok);

	return (0);
}
