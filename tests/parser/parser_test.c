/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:22:28 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 18:46:56 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "types.h"

const char *redir_type_to_str(int type)
{
	if (type == INPUT)
		return "INPUT";
	else if (type == OUTPUT)
		return "OUTPUT";
	else if (type == APPEND)
		return "APPEND";
	else if (type == HEREDOC)
		return "HEREDOC";
	return "UNKNOWN";
}

static void	print_pipeline(t_list *commands)
{
	t_list		*node = commands;
	t_command	*command;
	t_list		*redirs;
	t_redir		*redir;
	size_t		i;
	size_t		cmd_idx = 0;

	while (node)
	{
		command = (t_command *)node->content;
		ft_printf("cmds[%d]: argv=[", cmd_idx++);
		i = 0;
		while (command->argv[i])
		{
			ft_printf(CYAN"%s"RESET, command->argv[i]);
			if (command->argv[i + 1])
				ft_printf(", ");
			i++;
		}
		ft_printf("]"RESET);
		if (!command->redirs)
			ft_printf(",   redirs=[]\n");
		else
		{
			ft_printf(",   redirs=[");
			redirs = command->redirs;
			while (redirs)
			{
				redir = (t_redir *)redirs->content;
				ft_printf("{type="YELLOW"%s "RESET"filename="MAGENTA"%s"RESET" },",
					redir_type_to_str(redir->type), redir->filename);
				redirs = redirs->next;
			}
			ft_printf("]\n");
		}
		node = node->next;
	}
	ft_printf("\n");
}

int	main(void)
{
	t_list	*tokens;
	t_list	*commands;

	// ---------------- Test 1 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("cat")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("infile")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("foo")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("sort")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("-u")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("wc")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("-l")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(">")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("result.txt")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 1 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 2 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("echo")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("hello")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(">")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("out.txt")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 2 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 3 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("bar")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("<")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("input.txt")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("wc")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("-w")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 3 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 4 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("echo")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("more text")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(">>")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("logfile.txt")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 4 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 5 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("cat")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("EOF")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 5 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 6 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("ls")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 6 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 7 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("foo")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("<")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("input.txt")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(">>")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("output.log")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 7 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 8 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("cat")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("EOF")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("grep")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("foo bar")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("sort")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("-r")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("uniq")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("-c")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup(">>")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("result.log")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("|")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("echo")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("done")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 8 (Crazy Pipeline) ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	// ---------------- Test 9 ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("<<")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("EOF")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("wc")));
	ft_lstadd_back(&tokens, ft_lstnew(ft_strdup("-l")));

	if (!parse(tokens, &commands))
	{
		ft_printf("parse failed\n");
		return (1);
	}
	ft_printf("---- Test 9 ----\n");
	print_pipeline(commands);
	ft_lstclear(&tokens, free);
	ft_lstclear(&commands, free_command);

	return (0);
}
