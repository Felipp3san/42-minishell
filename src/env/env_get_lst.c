/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:33:26 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:37:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*env_get_lst(t_list *envp, const char *var)
{
	t_list	*node;
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
