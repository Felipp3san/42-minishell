/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:32:39 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:28:06 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

char	*env_get_arr(char **envp, const char *var)
{
	size_t	len;
	size_t	i;

	if (!envp || !var)
		return (NULL);
	len = ft_strlen(var);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0
			&& envp[i][len] == '=')
			return (&envp[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*env_get_lst(t_env *envp, const char *var)
{
	t_env	*node;
	char	*str;

	if (!envp || !var)
		return (NULL);
	node = envp;
	while (node)
	{
		str = node->name;
		if (ft_strcmp(str, var) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
