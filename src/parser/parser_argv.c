/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:48:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 14:58:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "libft.h"

t_command	*argv_realloc(t_command *cmd)
{
	char	**new_argv;

	new_argv = (char **) malloc(sizeof(char *) * (cmd->capacity + 16));
	if (!new_argv)
		return (NULL);
	ft_memcpy(new_argv, cmd->argv, sizeof(char *) * (cmd->size + 1));
	free(cmd->argv);
	cmd->argv = cmd->argv;
	cmd->capacity += 16;
	return (cmd);
}

t_command	*argv_append(t_command *cmd, const char *str)
{
	char	*word;

	if (cmd->size + 1 >= cmd->capacity)
	{
		if (!argv_realloc(cmd))
			return (NULL);
	}
	word = ft_strdup(str);
	if (!word)
		return (NULL);
	cmd->argv[cmd->size++] = word;
	cmd->argv[cmd->size] = NULL;
	return (cmd);
}
