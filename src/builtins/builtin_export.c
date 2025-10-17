/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:55 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:47:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./env_helpers/internal_helpers.h"
#include <stdlib.h>
#include "libft.h"
#include "builtins.h"
#include "utils.h"

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

	new_node = env_lst_new(name, value);
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
	if (split_assignment(variable, &var_name, &var_value) != SUCCESS)
		return (print_err_exit("export", "not a valid identifier", 1));
	if (is_valid_name(var_name) == ERROR)
	{
		free_var(var_name, var_value);
		return (print_err_exit("export", "not a valid identifier", 1));
	}
	node_found = search_variable(*env, var_name);
	if (node_found)
		ret_value = replace_variable(node_found, var_value);
	else
		ret_value = add_variable(env, var_name, var_value);
	return (ret_value);
}
