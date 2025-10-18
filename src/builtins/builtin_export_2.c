/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 23:28:08 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/17 23:28:08 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "builtins.h"
#include "types.h"

int	append_to_variable(t_env *node, char *value)
{
	char	*appended_value;

	if (!node)
		return (ERROR);
	appended_value = ft_strjoin(node->value, value);
	if (!appended_value)
		return (ERR_MALLOC);
	if (node->value)
		free(node->value);
	if (value)
		free(value);
	node->value = appended_value;
	return (SUCCESS);
}

char	*get_new_name(char *name, char *value)
{
	char	*new_name;
	char	*p_sign;

	p_sign = ft_strchr(name, '+');
	if (!p_sign)
		new_name = ft_strdup(name);
	else
		new_name = ft_substr(name, 0, p_sign - name);
	if (!new_name)
	{
		free_var(name, value);
		return (NULL);
	}
	free(name);
	return (new_name);
}

t_env	*search_variable(t_env *env, char *name, int plus)
{
	t_env	*temp;
	int		len;

	temp = env;
	len = ft_strlen(name);
	while (temp != NULL)
	{
		if (plus == 1)
		{
			if (ft_strncmp(name, temp->name, len - 1) == 0)
				return (temp);
		}
		else if (ft_strcmp(name, temp->name) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}
