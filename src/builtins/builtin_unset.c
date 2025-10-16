/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:10 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/16 18:19:57 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "./env_helpers/internal_helpers.h"
#include "builtins.h"
#include "utils.h"

void	free_var(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}

int	builtin_unset(t_env **env, char *variable)
{
	char	*var_name;
	char	*var_value;
	int		ret_value;

	if (!env || !*env)
		return (ERROR);
	if (!variable)
		return (SUCCESS);
	ret_value = split_assignment(variable, &var_name, &var_value);
	if (ret_value != SUCCESS)
		return (ERROR);
	if (is_valid_name(var_name) == ERROR)
	{
		free_var(var_name, var_value);
		return (ERROR);
	}
	if (!var_value)
		ret_value = env_var_delete(env, var_name);
	else
	{
		print_error("unset", variable, "not a valid identifier");
		free_var(var_name, var_value);
		return (ERROR);
	}
	free_var(var_name, var_value);
	return (ret_value);
}
