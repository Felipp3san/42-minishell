/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:18:50 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/10 14:06:20 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include <stdlib.h>

t_command	*cmd_lst_new(void)
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argv = (char **) malloc(sizeof(char *) * 16);
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argv[0] = NULL;
	cmd->size = 0;
	cmd->capacity = 16;
	cmd->redirs = NULL;
	cmd->next = NULL;
	cmd->previous = NULL;
	return (cmd);
}

void	cmd_lst_add_back(t_command **cmd_list, t_command *new_cmd)
{
	t_command	*last_cmd;

	if (!cmd_list || !new_cmd)
		return ;
	if (*cmd_list == NULL)
	{
		*cmd_list = new_cmd;
		new_cmd->previous = NULL;
		return ;
	}
	last_cmd = *cmd_list;
	while (last_cmd && last_cmd->next != NULL)
		last_cmd = last_cmd->next;
	last_cmd->next = new_cmd;
	new_cmd->previous = last_cmd;
}

size_t	cmd_lst_size(t_command *cmd)
{
	size_t	count;

	count = 0;
	if (!cmd)
		return (count);
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

void	cmd_lst_clear(t_command **cmd)
{
	t_command	*current;
	t_command	*next;
	size_t		i;

	if (!cmd)
		return ;
	current = *cmd;
	while (current)
	{
		next = current->next;
		if (current->argv)
		{
			i = 0;
			while (current->argv[i])
				free(current->argv[i++]);
			free(current->argv);
		}
		if (current->redirs)
			redir_lst_clear(&current->redirs);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

void	cmd_lst_delone(t_command **cmd)
{
	size_t	i;

	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->argv)
	{
		i = 0;
		while ((*cmd)->argv[i])
			free((*cmd)->argv[i++]);
		free((*cmd)->argv);
	}
	if ((*cmd)->redirs)
		redir_lst_clear(&(*cmd)->redirs);
	free((*cmd));
	*cmd = NULL;
}
