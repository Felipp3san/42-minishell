/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 19:30:04 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env_helpers/internal_helpers.h"
#include "types.h"

t_env	*search_variable(t_env *env, char *name)
{
	char	*sign;
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		sign = ft_strchr((char *)temp->content, '=');
		if (sign)
		{
			if (ft_strncmp(name, (char *)temp->content,
					sign - (char *)temp->content) == 0
				&& name[sign - (char *)temp->content] == '\0')
				return (temp);
		}
		else
		{
			if (ft_strcmp(name, (char *)temp->content) == 0)
				return (temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

static int	replace_variable(t_env *node, char *value)
{
	char	*new_value;
	char	*content;

	content = (char *)node->content;
	new_value = build_new_var_string(content, value);
	if (!new_value)
		return (ERR_MALLOC);
	free(node->content);
	node->content = new_value;
	return (SUCCESS);
}

static int	add_variable(t_env **env, char *name, char *value)
{
	t_env	*new_node;
	char	*new_content;

	new_node = NULL;
	if (!env)
		return (ERROR);
	new_content = build_new_var_string(name, value);
	if (!new_content)
		return (ERR_MALLOC);
	new_node = env_lst_new(new_content);
	if (!new_node)
	{
		free(new_content);
		return (ERR_MALLOC);
	}
	if (insert_in_list(env, new_node) != SUCCESS)
	{
		free(new_node->content);
		free(new_node);
		return (ERROR);
	}
	return (SUCCESS);
}

int	builtin_export(t_list **env, const char *variable)
{
	char	*var_name;
	char	*var_value;
	int		ret_value;
	t_env	*node_found;

	if (!env)
		return (ERROR);
	ret_value = split_assignment(variable, &var_name, &var_value);
	if (ret_value != SUCCESS)
		return (ret_value);
	if (is_valid_name(var_name) == ERROR)
	{
		free(var_name);
		free(var_value);
		return (ERROR);
	}
	node_found = search_variable(*env, var_name);
	if (node_found)
		ret_value = replace_variable(node_found, var_value);
	else
		ret_value = add_variable(env, var_name, var_value);
	free(var_name);
	free(var_value);
	return (ret_value);
}
