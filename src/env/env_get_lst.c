/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:33:26 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/13 23:56:39 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

char	*env_get_lst(t_env *envp, const char *var)
{
	t_env	*node;
	size_t	len;
	char	*str;

	if (!envp || !var)
		return (NULL);
	len = ft_strlen(var);
	node = envp;
	while (node)
	{
		str = node->name;
		if (ft_strncmp(str, var, len) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
