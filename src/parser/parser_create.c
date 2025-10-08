/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:47:16 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 13:12:14 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

t_redir	*redir_create(char *name, t_type type)
{
	t_redir	*redir;
	char	*str;

	redir = (t_redir *) malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	str = ft_strdup(name);
	if (!str)
	{
		free(redir);
		return (NULL);
	}
	if (type != HEREDOC)
	{
		redir->filename = str;
		redir->delimiter = NULL;
	}
	else
	{
		redir->delimiter = str;
		redir->filename = NULL;
	}
	redir->type = type;
	return (redir);
}

t_command	*command_create(void)
{
	t_command	*command;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = (char **) malloc(sizeof(char *) * 16);
	if (!command->argv)
	{
		free(command);
		return (NULL);
	}
	command->argv[0] = NULL;
	command->size = 0;
	command->capacity = 16;
	command->redirs = NULL;
	return (command);
}

t_command	*argv_realloc(t_command *command)
{
	char	**new_argv;

	new_argv = (char **) malloc(sizeof(char *) * (command->capacity + 16));
	if (!new_argv)
		return (NULL);
	ft_memcpy(new_argv, command->argv, sizeof(char *) * (command->size + 1));
	free(command->argv);
	command->argv = command->argv;
	command->capacity += 16;
	return (command);
}

t_command	*argv_append(t_command *command, const char *str)
{
	char	*word;

	if (command->size + 1 >= command->capacity)
	{
		if (!argv_realloc(command))
			return (NULL);
	}
	word = ft_strdup(str);
	if (!word)
		return (NULL);
	command->argv[command->size++] = word;
	command->argv[command->size] = NULL;
	return (command);
}
