/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:10 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 16:38:04 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "./env_helpers/internal_helpers.h"

static void	free_var(char *name, char *value)
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

	if(!env || !*env || !variable)
		return(ERROR);
	ret_value = split_assignment(variable, &var_name, &var_value);
	if (ret_value != SUCCESS)
		return (ret_value);
	if (is_valid_name(var_name) == ERROR)
	{
		free_var(var_name, var_value);
		return (ERROR);
	}
	if (!var_value)
		ret_value = env_delete(env, var_name);
	else
	{
		fprintf(stderr, "unset: `%s': not a valid identifier\n", variable);
		free_var(var_name, var_value);
		return (ERROR);
	}
	free_var(var_name, var_value);
	return (ret_value);
}
