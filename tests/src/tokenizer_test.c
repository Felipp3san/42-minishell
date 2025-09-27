/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:52:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 22:25:25 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "token.h"
#include "libft.h"
#include "types.h"

void print_tokens(const char *token, t_tokens *tokens)
{
	size_t i;

	i = 0;
	if (!tokens)
		return;
	ft_printf(CYAN"%s\n"RESET, token);
	while (tokens->tokens[i])
	{
		ft_printf(GREEN"%s"RESET, tokens->tokens[i]);
		if (i < tokens->size - 1)
			ft_printf(CYAN" - "RESET);
		i++;
	}
}

int	main(void)
{
	t_tokens	*tokens;
	size_t		i;

	const char *test_strings[] = {
		"echo hello world",
		"ls -la /tmp",
		"grep 'pattern' file.txt",
		"cat file.txt | sort | uniq",
		"echo \"A string with spaces\"",
		"echo 'Single quotes work too'",
		"ls > output.txt",
		"echo hello >> append.txt",
		"command arg1 arg2 | another_command arg3 > out.txt",
		"   spaces   before and after   ",
		"\"mixed 'quotes' inside\"",
		"echo >>> \"test\"",
		NULL
	};

	i = 0;
	while (test_strings[i])
	{
		tokens = tokenizer(test_strings[i]);
		if (!tokens)
		{
			ft_printf(RED"Tokenizer failed\n"RESET);
			return (EXIT_FAILURE);
		}
		print_tokens(test_strings[i], tokens);
		ft_printf("\n\n");
		tokens_free(tokens);
		free(tokens);
		i++;
	}
	return (EXIT_SUCCESS);
}
