/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_copy_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:42:54 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/13 19:42:54 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./internal_helpers.h"
#include "builtins.h"
#include "env.h"

static t_env	*copy_env_node(t_env *node)
{
	t_env	*new_node;

	if (!node)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (node->content)
	{
		new_node->content = ft_strjoin("declare -x ", node->content);
		if (!new_node->content)
		{
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->content = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_env	*copy_env_list(t_env *head)
{
	t_env	*copy;
	t_env	*cur;
	t_env	*node_copy;

	copy = NULL;
	cur = head;
	while (cur)
	{
		node_copy = copy_env_node(cur);
		if (!node_copy)
		{
			env_lst_clear(&copy);
			return NULL;
		}
		env_lst_add_back(&copy, node_copy);
		cur = cur->next;
	}
	return (copy);
}
