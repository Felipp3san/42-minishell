/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 16:45:36 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 13:37:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "minishell.h"
#include "buffer.h"
#include "libft.h"

char	*extract_var_name(char **arg)
{
	char	*start;

	if (!arg || !*arg)
		return (NULL);
	(*arg)++;
	start = *arg;
	if (**arg == '?')
	{
		(*arg)++;
		return (ft_strdup("?"));
	}
	while (**arg && (ft_isalnum(**arg) || **arg == '_'))
		(*arg)++;
	if (start == *arg)
		return (NULL);
	return (ft_substr(start, 0, (*arg) - start));
}

int	expand_var(t_shell *shell, char **arg, t_buffer *buffer)
{
	char	*var_name;
	char	*var_value;

	if (!arg || !*arg)
		return (ERROR);
	var_name = extract_var_name(arg);
	if (!var_name)
	{
		buffer_append(buffer, '$');
		return (SUCCESS);
	}
	if (ft_strcmp(var_name, "?") == 0)
	{
		var_value = ft_itoa(shell->last_exit_code);
		if (!var_value)
			return (free(var_name), ERROR);
		buffer_append_str(buffer, var_value);
		free(var_value);
	}
	else
	{
		var_value = env_get_lst(shell->env_lst, var_name);
		buffer_append_str(buffer, var_value);
	}
	return (free(var_name), SUCCESS);
}

char	*expand_vars(t_shell *shell, char *arg)
{
	char			*expanded;
	t_buffer		*buffer;
	t_quote_state	quote;

	ft_memset(&quote, 0, sizeof(quote));
	if (!buffer_create(&buffer))
		return (NULL);
	while (*arg)
	{
		if (*arg == '\'' && !quote.double_opened)
			quote.single_opened = !quote.single_opened;
		else if (*arg == '\"' && !quote.single_opened)
			quote.double_opened = !quote.double_opened;
		else if (*arg == '$' && !quote.single_opened)
		{
			if (expand_var(shell, &arg, buffer) != SUCCESS)
				return (buffer_free(buffer), NULL);
			continue ;
		}
		else if (!buffer_append(buffer, *arg))
			return (buffer_free(buffer), NULL);
		arg++;
	}
	expanded = buffer_flush(buffer);
	return (buffer_free(buffer), expanded);
}

t_command	*expand(t_shell *shell)
{
	t_command	*cmd_node;
	char		*expanded;
	size_t		i;

	if (!shell || !shell->commands)
		return (NULL);
	cmd_node = shell->commands;
	while (cmd_node)
	{
		i = 0;
		while (cmd_node->argv[i])
		{
			expanded = expand_vars(shell, cmd_node->argv[i]);
			if (!expanded || *expanded == '\0')
			{
				argv_remove_index(cmd_node, i);
				continue ;
			}
			free(cmd_node->argv[i]);
			cmd_node->argv[i] = expanded;
			i++;
		}
		cmd_node = cmd_node->next;
	}
	return (shell->commands);
}
