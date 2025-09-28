/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:52:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 01:18:07 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "tokens.h"
#include "libft.h"
#include "types.h"

void print_tokens(const char *token, t_tokens *tokens)
{
	size_t	i;
	char	*mode;

	i = 0;
	if (!tokens)
		return;
	ft_printf(CYAN"%s\n"RESET, token);
	while (tokens->tokens[i])
	{
		if (tokens->tokens[i]->quote == NO_QUOTE)
			mode = "NO_QUOTE";
		else if (tokens->tokens[i]->quote == SINGLE_QUOTE)
			mode = "SINGLE_QUOTE";
		else if (tokens->tokens[i]->quote == DOUBLE_QUOTE)
			mode = "DOUBLE_QUOTE";
		else
			mode = "UNSET";
		ft_printf(GREEN"%s[%s]"RESET, tokens->tokens[i]->value, mode);
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
		//NULL,
		" ",
		"",
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

		// --- ENV VAR TESTS ---
		"echo $HOME",
		"echo \"$HOME\"",
		"echo '$HOME'",
		"echo $USER",
		"echo \"$USER is logged in\"",
		"echo 'User is $USER'",  // should not expand inside single quotes
		"echo Path: $PATH",
		"echo \"Path is $PATH\"",
		"echo '$PATH not expanded here'",
		"echo Text $HOME more text",
		"echo \"Text $HOME more text\"",
		"echo 'Text $HOME more text'",
		"echo \"$USER's home is $HOME\"",
		"echo '$USER's home is $HOME'", // tricky quotes
		"echo \"Mix 'single $USER' and double $HOME\"",

		// Simple mixed quotes
		"echo 'Hello \"world\"'",           // single quotes wrap, double quotes inside are literal
		"echo \"Hello 'world'\"",           // double quotes wrap, single quotes inside are literal
		"echo \"Hello \\\"world\\\"\"",     // escaped quotes inside double quotes
		"echo 'It\\'s fine'",               // escaped single quote inside single quotes
		"echo \"It's fine\"",               // single quote inside double quotes

		// Operators with spaces and quotes
		"echo hello > output.txt",          // output redirection, no quotes
		"echo \"hello\" > \"output.txt\"",  // redirection with quotes
		"cat < 'input file.txt'",           // input redirection with single quotes
		"grep pattern << EOF",              // here-doc
		"command arg1 | command2 arg2 >> log.txt", // pipe + append

		// Multiple operators together
		"echo a >>> file.txt",              // triple '>' operator
		"echo a >> file1.txt >> file2.txt", // multiple append operators
		"echo a | grep b | sort",           // multiple pipes
		"command <<< 'here string'",        // here-string with single quotes

		// Nested and tricky quotes
		"echo \"He said 'hello $USER'\"",   // single inside double, $USER expands
		"echo 'He said \"hello $USER\"'",   // double inside single, $USER literal
		"echo \"Mix \\\"quotes\\\" and $HOME\"", // escaped double inside double quotes, env expands
		"echo 'Mix \\'quotes\\' and $HOME'",    // escaped single inside single quotes, env literal

		// Edge cases
		"echo \"Unclosed quote test",       // unclosed double quote
		"echo 'Unclosed quote test",        // unclosed single quote
		"echo \"Nested 'single' inside \"double\"\"", // invalid nested double quotes inside double
		"echo 'Nested \"double\" inside 'single''", // invalid nested single quotes

		// Env var edge cases
		"echo $$",                          // pid variable, no quotes
		"echo \"$?\"",                       // last command status inside double quotes
		"echo '$?'",                         // last command status inside single quotes
		"echo $HOME$USER",                   // concatenated env vars, no quotes
		"echo \"$HOME$USER\"",               // concatenated env vars inside double quotes
		"echo '$HOME$USER'",                 // concatenated env vars inside single quotes, literal
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
