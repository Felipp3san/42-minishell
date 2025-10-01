/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:52:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 19:50:28 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "libft.h"
#include "types.h"

void print_tokens(const char *str, t_list *head)
{
	t_list	*node;

	if (!head)
		return;
	ft_printf(CYAN"%s\n"RESET, str);
	node = head;
	while (node)
	{
		ft_printf(GREEN"%s"RESET, (char *) node->content);
		if (node->next != NULL)
			ft_printf(CYAN" - "RESET);
		node = node->next;
	}
}

int	main(void)
{
	t_list		*tokens;
	size_t		i;
	t_status	err;

	tokens = NULL;
	const char *test_strings[] = {
		" ",
		"",
		"echo hello world",
		"echo\'hello world\'",
		"ls -la /tmp",
		"echo >>> \"test\"",
		"grep 'pattern' file.txt",
		"cat file.txt | sort | uniq",
		"echo \"A string with spaces\"",
		"echo 'Single quotes work too'",
		"ls > output.txt",
		"echo hello >> append.txt",
		"command arg1 arg2 | another_command arg3 > out.txt",
		"   spaces   before and after   ",
		"\"mixed 'quotes' inside\"",
		"echo >>\"test\"",
		"echo >>test",
		"echo >>> \"test\"",
		"echo <<|> \"test\"",

		// --- ENV VAR TESTS ---
		"echo $HOME",
		"echo \"$HOME\"",
		"echo '$HOME'",
		"echo $USER",
		"echo \"$USER\"s",
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
		err = tokenize(test_strings[i], &tokens);
		if (err != SUCCESS)
		{
			if (err == ERROR)
			{
				ft_printf(CYAN"%s\n"RESET, test_strings[i]);
				ft_printf(YELLOW"Open quotes detected.\n"RESET);
			}
			if (err == ERR_MALLOC)
			{
				ft_printf(RED"Tokenizer failed\n"RESET);
				return (EXIT_FAILURE);
			}
		}
		print_tokens(test_strings[i], tokens);
		ft_printf("\n\n");
		ft_lstclear(&tokens, free);
		i++;
	}
	return (EXIT_SUCCESS);
}
