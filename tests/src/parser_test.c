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
#include "token.h"
#include "command.h"
#include "parser.h"

int	main(void)
{
	t_tokens	*tokens;
	t_token		*token;
	t_token		*token2;
	t_list		*node;

	t_commands	*commands;

	tokens = NULL;
	commands = NULL;
	token = (t_token *) malloc(sizeof(t_token));
	token->str = ft_strdup("echo");

	token2 = (t_token *) malloc(sizeof(t_token));
	token2->str = ft_strdup("Hello world");

	node = ft_lstnew((void *) token);
	if (!node)
	{
		ft_printf("Error...");
		return (1);
	}
	ft_lstadd_back(&tokens, node);

	node = ft_lstnew((void *) token2);
	if (!node)
	{
		ft_printf("Error...");
		return (1);
	}
	ft_lstadd_back(&tokens, node);

	node = tokens;
	while (node)
	{
		ft_printf("%s\n", get_token_value((t_token *) node->content));
		node = node->next;
	}

	parser(tokens, &commands);

	return (0);
}
