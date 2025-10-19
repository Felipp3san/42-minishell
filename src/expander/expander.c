/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:45:36 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 20:11:12 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "minishell.h"
#include "libft.h"
#include "types.h"

char	*expand_str(t_shell *shell, char *str)
{
	size_t	i;
	char	*ret;
	char	*temp;

	ret = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			temp = handle_squote(str, &i);
		else if (str[i] == '\"')
			temp = handle_dquote(shell, str, &i);
		else if (str[i] == '$')
			temp = handle_dollar(shell, str, &i, FALSE);
		else
			temp = handle_normal(str, &i);
		if (!temp)
			continue ;
		ret = ft_strjoin_free(ret, temp);
		if (!ret)
			return (NULL);
	}
	return (ret);
}

void	expand_args(t_shell *shell, t_command *cmd)
{
	char	*expanded;
	size_t	i;

	i = 0;
	while (cmd->argv[i])
	{
		expanded = expand_str(shell, cmd->argv[i]);
		if (!expanded)
		{
			argv_remove_index(cmd, i);
			continue ;
		}
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
		i++;
	}
}

t_command	*expand(t_shell *shell)
{
	t_command	*cmd_node;

	if (!shell || !shell->commands)
		return (NULL);
	cmd_node = shell->commands;
	while (cmd_node)
	{
		expand_args(shell, cmd_node);
		if (expand_heredoc(shell, cmd_node) == ERROR)
			return (NULL);
		cmd_node = cmd_node->next;
	}
	return (shell->commands);
}
