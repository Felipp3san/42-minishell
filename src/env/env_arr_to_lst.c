/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr_to_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:25:42 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 15:47:46 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"

t_env	*env_arr_to_lst(char **envp)
{
	t_env	*clone;
	t_env	*node;
	char	*content;
	size_t	i;

	if (!envp)
		return (NULL);
	clone = NULL;
	i = 0;
	while (envp[i])
	{
		content = ft_strdup(envp[i]);
		if (!content)
			return (env_free_all(clone), NULL);
		node = env_new(content);
		if (!node)
		{
			free(content);
			return (env_free_all(clone), NULL);
		}
		env_append(&clone, node);
		i++;
	}
	return (clone);
}
