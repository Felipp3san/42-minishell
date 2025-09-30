/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:22:28 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 15:39:17 by fde-alme         ###   ########.fr       */
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

static void print_pipeline(t_list *commands)
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
				ft_printf("{type="YELLOW"%s "RESET"filename="MAGENTA"%s"RESET" },", redir_type_to_str(redir->type), redir->filename);
				redirs = redirs->next;
			}
			ft_printf("]\n");
		}
		node = node->next;
	}
	ft_printf("\n");
}

int main(void)
{
	t_list		*tokens;
	t_list		*commands;

	// ---------------- Test 1: pipeline with output redir ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("infile"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("foo"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("sort"));
	ft_lstadd_back(&tokens, ft_lstnew("-u"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("wc"));
	ft_lstadd_back(&tokens, ft_lstnew("-l"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("result.txt"));

	parser(tokens, &commands);
	ft_printf("---- Test 1 ----\n");
	print_pipeline(commands);

	// ---------------- Test 2: single command with output ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew("echo"));
	ft_lstadd_back(&tokens, ft_lstnew("hello"));
	ft_lstadd_back(&tokens, ft_lstnew(">"));
	ft_lstadd_back(&tokens, ft_lstnew("out.txt"));

	parser(tokens, &commands);
	ft_printf("---- Test 2 ----\n");
	print_pipeline(commands);

	// ---------------- Test 3: input redirection with pipe ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("bar"));
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("input.txt"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("wc"));
	ft_lstadd_back(&tokens, ft_lstnew("-w"));

	parser(tokens, &commands);
	ft_printf("---- Test 3 ----\n");
	print_pipeline(commands);

	// ---------------- Test 4: append redirection ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew("echo"));
	ft_lstadd_back(&tokens, ft_lstnew("more text"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("logfile.txt"));

	parser(tokens, &commands);
	ft_printf("---- Test 4 ----\n");
	print_pipeline(commands);

	// ---------------- Test 5: heredoc ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));

	parser(tokens, &commands);
	ft_printf("---- Test 5 ----\n");
	print_pipeline(commands);

	// ---------------- Test 6: command without arguments ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew("ls"));

	parser(tokens, &commands);
	ft_printf("---- Test 6 ----\n");
	print_pipeline(commands);

	// ---------------- Test 7: multiple redirections ----------------
	tokens = NULL; commands = NULL;
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("foo"));
	ft_lstadd_back(&tokens, ft_lstnew("<"));
	ft_lstadd_back(&tokens, ft_lstnew("input.txt"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("output.log"));

	parser(tokens, &commands);
	ft_printf("---- Test 7 ----\n");
	print_pipeline(commands);

	// ---------------- Test 8: “crazy” complex pipeline ----------------
	tokens = NULL; commands = NULL;

	// First command: cat << EOF | grep "foo bar"
	ft_lstadd_back(&tokens, ft_lstnew("cat"));
	ft_lstadd_back(&tokens, ft_lstnew("<<"));
	ft_lstadd_back(&tokens, ft_lstnew("EOF"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("grep"));
	ft_lstadd_back(&tokens, ft_lstnew("\"foo bar\""));

	// Second command: sort -r | uniq -c >> result.log
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("sort"));
	ft_lstadd_back(&tokens, ft_lstnew("-r"));
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("uniq"));
	ft_lstadd_back(&tokens, ft_lstnew("-c"));
	ft_lstadd_back(&tokens, ft_lstnew(">>"));
	ft_lstadd_back(&tokens, ft_lstnew("result.log"));

	// Third command: echo "done"
	ft_lstadd_back(&tokens, ft_lstnew("|"));
	ft_lstadd_back(&tokens, ft_lstnew("echo"));
	ft_lstadd_back(&tokens, ft_lstnew("\"done\""));

	parser(tokens, &commands);
	ft_printf("---- Test 8 (Crazy Pipeline) ----\n");
	print_pipeline(commands);

	return (0);
}
