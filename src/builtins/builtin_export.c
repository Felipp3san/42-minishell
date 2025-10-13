/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/13 23:35:45 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env_helpers/internal_helpers.h"
#include "builtins.h"

t_env	*search_variable(t_env *env, char *name)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(name, temp->name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static int	replace_variable(t_env *node, char *value)
{
	if (!node)
		return (ERROR);
	if (node->value)
		free(node->value);
	node->value = value;
	return (SUCCESS);
}

static int	add_variable(t_env **env, char *name, char *value)
{
	t_env	*new_node;

	new_node  = env_lst_new(name, value);
	if (!new_node)
		return (ERROR);
	env_lst_add_back(env, new_node);
	return (SUCCESS);
}

int	builtin_export(t_env **env, const char *variable)
{
	char	*var_name;
	char	*var_value;
	int		ret_value;
	t_env	*node_found;

	if (!env)
		return (ERROR);
	if (!variable)
		ret_value = export_print_list(env);
	ret_value = split_assignment(variable, &var_name, &var_value);
	if (ret_value != SUCCESS)
		return (ret_value);
	if (is_valid_name(var_name) == ERROR)
	{
		free_var(var_name, var_value);
		return (ERROR);
	}
	node_found = search_variable(*env, var_name);
	if (node_found)
		ret_value = replace_variable(node_found, var_value);
	else
		ret_value = add_variable(env, var_name, var_value);
	return (ret_value);
}
