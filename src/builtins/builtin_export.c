/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/21 16:33:52 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtins.h"
#include "utils.h"
#include "types.h"

int	replace_variable(t_env *node, char *value)
{
	if (!node)
		return (ERROR);
	if (node->value)
		free(node->value);
	node->value = value;
	return (SUCCESS);
}

int	add_variable(t_env **env, char *name, char *value, int plus)
{
	t_env	*new_node;
	char	*new_name;

	new_name = NULL;
	if (plus == 1)
	{
		new_name = get_new_name(name, value);
		if (!new_name)
			return (ERROR);
	}
	else
		new_name = name;
	new_node = env_lst_new(new_name, value);
	if (!new_node)
	{
		free_var(new_name, value);
		return (ERROR);
	}
	env_lst_add_back(env, new_node);
	return (SUCCESS);
}

int	append_or_replace(t_env *node, int plus, char *var_name, char *var_value)
{
	if (node_found)
	{
		if (plus == 1 && node_found->value)
		{
			if (append_to_variable(node_found, var_value) != SUCCESS)
			{
				free_var(var_name, var_value);
				return (ERROR);
			}
		}
		else
		{
			if (replace_variable(node_found, var_value) != SUCCESS)
			{
				free_var(var_name, var_value);
				return (ERROR);
			}
		}
	}
	free(var_name);
	return (SUCCESS);
}

int	process_variable(t_env **env, char *variable)
{
	int		plus;
	int		ret_value;
	t_env	*node_found;
	char	*var_name;
	char	*var_value;

	plus = 0;
	node_found = NULL;
	if (split_assignment(variable, &var_name, &var_value) != SUCCESS)
		return (print_error_return("export", "not a valid identifier", 1));
	if (is_valid_name(var_name, &plus) == ERROR)
	{
		free_var(var_name, var_value);
		return (print_error_return("export", "not a valid identifier", 1));
	}
	node_found = search_variable(*env, var_name, plus);
	if (node_found)
		ret_value = append_or_replace(node_found, plus, var_name, var_value);
	else
		ret_value = add_variable(env, var_name, var_value, plus);
	return (ret_value);
}

int	builtin_export(t_env **env, char **variable)
{
	int	i;
	int	ret_value;

	i = 1;
	ret_value = SUCCESS;
	if (!env)
		return (ERROR);
	if (!variable[1])
		return (export_print_list(env));
	while (variable[i])
	{
		if (process_variable(env, variable[i]) != SUCCESS)
			return (1);
		i++;
	}
	return (ret_value);
}
