/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:32:53 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/14 00:08:36 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

char	*get_clone(char *name, char *value)
{
	char	*clone;
	char	*temp;

	if (value)
	{
		temp = ft_strjoin(name, "=");
		if (!temp)
			return (NULL);
		clone = ft_strjoin(temp, value);
		free(temp);
		return (clone);
	}
	return (ft_strdup(name));
}

char	**env_list_to_arr(t_env *envp)
{
	char	**clone;
	t_env	*node;
	size_t	size;
	size_t	i;

	if (!envp)
		return (NULL);
	size = env_lst_size(envp);
	clone = (char **) malloc(sizeof(char *) * (size + 1));
	if (!clone)
		return (NULL);
	i = 0;
	node = envp;
	while (node)
	{
		clone[i] = get_clone(node->name, node->value);
		if (!clone[i])
			return (env_free(clone), NULL);
		node = node->next;
		i++;
	}
	clone[i] = NULL;
	return (clone);
}
