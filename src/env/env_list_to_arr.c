/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:32:53 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 17:08:00 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"

char	**env_list_to_arr(t_env *envp)
{
	char	**clone;
	t_env	*node;
	size_t	size;
	size_t	i;

	if (!envp)
		return (NULL);
	size = env_size(envp);
	clone = (char **) malloc(sizeof(char *) * (size + 1));
	if (!clone)
		return (NULL);
	i = 0;
	node = envp;
	while (node)
	{
		clone[i] = ft_strdup(node->content);
		if (!clone[i])
			return (env_free(clone), NULL);
		node = node->next;
		i++;
	}
	clone[i] = NULL;
	return (clone);
}
