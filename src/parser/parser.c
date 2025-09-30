/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:19:47 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 15:59:53 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "types.h"
#include "command.h"

t_bool	str_is_operator(char *token)
{
	return (ft_strcmp(token, "|") == 0);
}

t_command	*command_add(t_tokens *tokens, size_t size, t_commands **out)
{
	t_command	*command;
	size_t		i;

	command = command_init(size, WORD);
	if (!command)
		return (NULL);
	if (!commands_append(out, command))
		return (NULL);
	i = 0;
	while (i < size)
	{
		command->comm_arr[i] = get_token_value((tokens + i)->content);
		i++;
	}
	return (command);
}

int	parser(t_tokens *tokens, t_commands **out)
{
	t_tokens	*token_node;
	char		*token_value;
	size_t		count;

	token_node = tokens;
	while (token_node)
	{
		count = 0;
		token_value = get_token_value(token_node->content);
		while (token_node && !str_is_operator(token_value))
		{
			count++;
			token_node = token_node->next;
			if (token_node != NULL)
				token_value = get_token_value(token_node->content);
		}
		if (count > 0)
		{
			if (!command_add(tokens, count, out))
				return (ERR_MALLOC);
		}
		if (ft_strcmp(token_value, "|") == 0)
		{
			if (!command_add(tokens, count, out))
				return (ERR_MALLOC);
		}
		token_node = token_node->next;
	}
	return (SUCCESS);
}
