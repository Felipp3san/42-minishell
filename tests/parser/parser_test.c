/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:48:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 16:21:13 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "parser.h"
#include "tokenizer.h"
#include "libft.h"
#include "types.h"
#include "command.h"
#include "debug.h"

int	main(void)
{
	t_token		*tokens;
	t_command	*commands;
	size_t		i;

	tokens = NULL;
	commands = NULL;

	const char *test_strings[] = {
		"echo hello world",
		"ls -la /tmp",
		"echo \"Hello World\"",
		"cat file.txt | grep test",
		"echo hello > file.txt",
		"echo hello >> append.txt",
		"cat < infile | grep data > outfile",
		"echo 'Single quotes work too'",
		"echo $USER",
		"echo \"$HOME is home\"",
		"echo a >>> file.txt",
		"command arg1 arg2 | another_command arg3 > out.txt",
		"grep 'pattern' < input.txt | sort | uniq > output.txt",
		"   spaces   before and after   ",
		"echo \"Mix 'single $USER' and double $HOME\"",
		"echo '$USER's home is $HOME'", // tricky one
		"echo << EOF",
		"echo <<|> \"test\"",
		NULL
	};

	i = 0;
	while (test_strings[i])
	{
		char *input = ft_strdup(test_strings[i]);
		if (!input)
			return (ft_printf(RED"malloc error\n"RESET), EXIT_FAILURE);

		ft_printf(CYAN"Input: %s\n"RESET, test_strings[i]);
		tokens = tokenize(input);
		if (!tokens)
		{
			ft_printf(RED"Tokenizer failed\n\n"RESET);
			free(input);
			i++;
			continue;
		}

		commands = parse(tokens);
		if (!commands)
		{
			ft_printf(RED"Parser failed\n\n"RESET);
			token_lst_clear(&tokens);
			free(input);
			i++;
			continue;
		}

		print_command_list(commands);
		ft_printf("\n");

		cmd_lst_clear(&commands);
		token_lst_clear(&tokens);
		free(input);
		i++;
	}
	return (EXIT_SUCCESS);
}
