/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr_to_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:25:42 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/13 23:32:05 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtins.h"

t_env	*env_arr_to_lst(char **envp)
{
	t_env	*clone;
	t_env	*node;
	char	*name;
	char	*value;
	size_t	i;

	if (!envp)
		return (NULL);
	clone = NULL;
	i = 0;
	while (envp[i])
	{
		split_assignment(ft_strdup(envp[i]), &name, &value);
		if (!name)
			return (env_lst_clear(&clone), NULL);
		node = env_lst_new(name, value);
		if (!node)
		{
			free_var(name, value);
			return (env_lst_clear(&clone), NULL);
		}
		env_lst_add_back(&clone, node);
		i++;
	}
	return (clone);
}
