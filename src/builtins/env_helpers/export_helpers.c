/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:32:14 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/17 12:49:30 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_helpers.h"
#include "libft.h"
#include "types.h"

static int	get_only_name(const char *var, char **out_name, char **out_value)
{
	*out_name = ft_strdup(var);
	if (!*out_name)
		return (ERR_MALLOC);
	*out_value = NULL;
	return (SUCCESS);
}

int	split_assignment(const char *variable, char **out_name, char **out_value)
{
	char	*sign;
	size_t	name_len;

	if (!variable || !out_name || !out_value)
		return (ERROR);
	sign = ft_strchr(variable, '=');
	if (!sign)
		return (get_only_name(variable, out_name, out_value));
	name_len = (size_t)(sign - variable);
	if (name_len == 0)
		return (ERROR);
	*out_name = malloc((name_len + 1) * sizeof(char));
	if (!*out_name)
		return (ERR_MALLOC);
	ft_strlcpy(*out_name, variable, name_len + 1);
	*out_value = ft_strdup(sign + 1);
	if (!*out_value)
	{
		free(*out_name);
		*out_name = NULL;
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (ERROR);
	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (ERROR);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
