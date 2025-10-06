/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:19:47 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 19:27:43 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_internal.h"
#include "types.h"

static int	parse_token(t_list **node, t_command **command)
{
	t_redir	*redir;
	t_type	type;

	type = get_token_type((*node)->content);
	if (is_word(type))
	{
		if (!argv_append(*command, (*node)->content))
			return (ERR_MALLOC);
	}
	else if (is_redir(type))
	{
		*node = (*node)->next;
		redir = redir_create((*node)->content, type);
		if (!redir)
			return (ERR_MALLOC);
		ft_lstadd_back(&(*command)->redirs, ft_lstnew(redir));
	}
	return (SUCCESS);
}

static t_command	*parser(t_list **node)
{
	t_command	*command;

	command = command_create();
	if (!command)
		return (NULL);
	while (*node && get_token_type((*node)->content) != PIPE)
	{
		if (parse_token(node, &command) == ERR_MALLOC)
		{
			free_command(command);
			return (NULL);
		}
		*node = (*node)->next;
	}
	return (command);
}

t_list	*parse(t_list *tokens, t_list **out)
{
	t_command	*command;
	t_list		*node;

	node = tokens;
	while (node)
	{
		command = parser(&node);
		if (!command)
		{
			ft_lstclear(out, free_command);
			*out = NULL;
			return (NULL);
		}
		ft_lstadd_back(out, ft_lstnew(command));
		if (node && get_token_type(node->content) == PIPE)
			node = node->next;
	}
	return (*out);
}
