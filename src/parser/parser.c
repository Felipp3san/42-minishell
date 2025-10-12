/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:42:00 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 12:35:50 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "libft.h"
#include "types.h"
#include "utils.h"

static char	*get_redir_value(char *token_value, int *expand)
{
	if (ft_strchr(token_value, '\"') || ft_strchr(token_value, '\''))
	{
		*expand = FALSE;
		return (remove_quotes(token_value));
	}
	*expand = TRUE;
	return (ft_strdup(token_value));
}

static int	handle_redir(t_token **token, t_command *command)
{
	t_redir_data	data;
	t_redir			*redir;

	if (!(*token) || !(*token)->next)
		return (ERROR);
	data.expand_heredoc = TRUE;
	data.heredoc_fd = -1;
	data.value = get_redir_value((*token)->next->value, &data.expand_heredoc);
	if (!data.value)
		return (ERR_MALLOC);
	if (is_heredoc((*token)->type))
	{
		data.heredoc_fd = parser_heredoc(data.value);
		if (data.heredoc_fd == -1)
			return (free(data.value), ERROR);
	}
	redir = redir_lst_new(&data, (*token)->type);
	if (!redir)
		return (free(data.value), ERR_MALLOC);
	redir_lst_add_back(&command->redirs, redir);
	*token = (*token)->next;
	return (SUCCESS);
}

static int	parse_token(t_token **token, t_command *command)
{
	int	status;

	if (is_word((*token)->type))
	{
		if (!argv_append(command, (*token)->value))
			return (ERR_MALLOC);
	}
	else if (is_redir((*token)->type))
	{
		status = handle_redir(token, command);
		if (status != SUCCESS)
			return (status);
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
			break ;
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
		if (!new_cmd->argv[0])
			cmd_lst_delone(&new_cmd);
		else
			cmd_lst_add_back(&cmd_list, new_cmd);
	}
	return (cmd_list);
}
