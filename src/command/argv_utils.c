/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:09:53 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 18:39:58 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
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

void	argv_remove_index(t_command *cmd, size_t idx)
{
	if (!cmd || !cmd->argv || idx >= cmd->size)
		return ;
	if (cmd->argv[idx])
		free(cmd->argv[idx]);
	while (cmd->argv[idx])
	{
		cmd->argv[idx] = cmd->argv[idx + 1];
		idx++;
	}
	cmd->argv[idx] = NULL;
	if (cmd->size > 0)
		cmd->size--;
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
