/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:33:26 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 18:30:27 by jfernand         ###   ########.fr       */
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
		str = node->content;
		if (ft_strncmp(str, var, len) == 0
			&& str[len] == '=')
			return (&str[len + 1]);
		node = node->next;
	}
	return (NULL);
}
