/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:24:14 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/04 18:51:37 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

char	*env_get(t_list *envp, const char *var)
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

void	env_free(char **envp)
{
	size_t	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

t_list	*env_clone(char **envp)
{
	t_list	*clone;
	t_list	*node;
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
			return (ft_lstclear(&clone, free), NULL);
		node = ft_lstnew(content);
		if (!node)
		{
			free(content);
			return (ft_lstclear(&clone, free), NULL);
		}
		ft_lstadd_back(&clone, node);
		i++;
	}
	return (clone);
}

char	**env_list_to_arr(t_list *envp)
{
	char	**clone;
	t_list	*node;
	size_t	size;
	size_t	i;

	if (!envp)
		return (NULL);
	size = ft_lstsize(envp);
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
