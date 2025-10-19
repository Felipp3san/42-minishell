/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:42:00 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:11:47 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parser_internal.h"
#include "types.h"
#include "command.h"

static int	handle_redir(t_token **token, t_command *command)
{
	t_redir	*redir;
	char	*value;
	int		expand;

	if (!(*token) || !(*token)->next)
		return (ERROR);
	expand = should_expand_heredoc((*token)->next->value);
	value = remove_quotes((*token)->next->value);
	redir = redir_lst_new(value, expand, (*token)->type);
	if (!redir)
		return (free(value), ERR_MALLOC);
	redir_lst_add_back(&command->redirs, redir);
	*token = (*token)->next;
	return (SUCCESS);
}

static int	parse_token(t_token **token, t_command *command)
{
	if (is_word((*token)->type))
	{
		if (!argv_append(command, (*token)->value))
			return (ERR_MALLOC);
	}
	else if (is_redir((*token)->type))
		return (handle_redir(token, command));
	return (SUCCESS);
}

static t_command	*tokens_to_command(t_token **token)
{
	t_command	*new_cmd;

	new_cmd = cmd_lst_new();
	if (!new_cmd)
		return (NULL);
	while (*token && (*token)->type != PIPE)
	{
		if (parse_token(token, new_cmd) != SUCCESS)
		{
			cmd_lst_delone(&new_cmd);
			return (NULL);
		}
		*token = (*token)->next;
	}
	if (*token && (*token)->type == PIPE)
		*token = (*token)->next;
	return (new_cmd);
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
		new_cmd = tokens_to_command(&token);
		if (!new_cmd)
			return (cmd_lst_clear(&cmd_list), NULL);
		cmd_lst_add_back(&cmd_list, new_cmd);
	}
	return (cmd_list);
}
