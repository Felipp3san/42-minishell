/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:42:00 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 18:27:35 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "libft.h"
#include "types.h"

static int	parse_token(t_token **token, t_command *command)
{
	t_redir	*redir;
	char	*value;

	if (is_word((*token)->type))
	{
		if (!argv_append(command, (*token)->value))
			return (ERR_MALLOC);
	}
	else if (is_redir((*token)->type))
	{
		(*token) = (*token)->next;
		value = ft_strdup((*token)->value);
		if (!value)
			return (ERR_MALLOC);
		redir = redir_lst_new(value, (*token)->previous->type);
		if (!redir)
			return (ERR_MALLOC);
		redir_lst_add_back(&command->redirs, redir);
	}
	(*token) = (*token)->next;
	return (SUCCESS);
}

t_token	*syntax_check(t_token *token)
{
	if (token->type == PIPE)
		return (token);
	while (token)
	{
		if (!token->next && is_sep(token->type))
			break;
		if (is_redir(token->type) && is_sep(token->next->type))
			break ;
		if (token->type == PIPE && token->next->type == PIPE)
			break ;
		token = token->next;
	}
	return (token);
}

t_command	*parse(t_token *token)
{
	t_command	*cmd_list;
	t_command	*new_cmd;
	t_token		*error;

	cmd_list = NULL;
	error = syntax_check(token);
	if (error)
		return (print_parser_err(error), NULL);
	while (token)
	{
		new_cmd = cmd_lst_new();
		if (!new_cmd)
			return (cmd_lst_clear(&cmd_list), NULL);
		while (token && token->type != PIPE)
		{
			if (parse_token(&token, new_cmd) != SUCCESS)
			{
				cmd_lst_delone(&new_cmd);
				return (cmd_lst_clear(&cmd_list), NULL);
			}
		}
		if (token)
			token = token->next;
		cmd_lst_add_back(&cmd_list, new_cmd);
	}
	return (cmd_list);
}
