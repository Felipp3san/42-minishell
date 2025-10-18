/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:29:03 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/18 00:56:39 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "builtins.h"

static char	*get_clone(char *name, char *value);

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
		split_assignment(envp[i], &name, &value);
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
			return (env_arr_free(clone), NULL);
		node = node->next;
		i++;
	}
	clone[i] = NULL;
	return (clone);
}

static char	*get_clone(char *name, char *value)
{
	char	*clone;
	char	*temp;

	if (value && name)
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
