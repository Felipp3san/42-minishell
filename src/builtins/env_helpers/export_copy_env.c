/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_copy_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:42:54 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/17 12:49:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_helpers.h"
#include "libft.h"
#include "types.h"
#include "env.h"

static int	copy_name(t_env *node, t_env *new_node)
{
	if (node->name)
	{
		new_node->name = ft_strdup(node->name);
		if (!new_node->name)
		{
			free(new_node);
			return (ERR_MALLOC);
		}
		return (SUCCESS);
	}
	return (ERR_MALLOC);
}

static int	copy_value(t_env *node, t_env *new_node)
{
	if (node->value)
	{
		new_node->value = ft_strdup(node->value);
		if (!new_node->value)
		{
			free(new_node->name);
			new_node->name = NULL;
			free(new_node);
			return (ERR_MALLOC);
		}
	}
	else
		new_node->value = NULL;
	return (SUCCESS);
}

static int	copy_content(t_env *node, t_env *new_node)
{
	int	ret;

	ret = copy_name(node, new_node);
	if (ret != SUCCESS)
		return (ret);
	ret = copy_value(node, new_node);
	if (ret != SUCCESS)
		return (ret);
	return (ret);
}

static t_env	*copy_env_node(t_env *node)
{
	t_env	*new_node;

	if (!node)
		return (NULL);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (copy_content(node, new_node) != SUCCESS)
		return (NULL);
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
			return (NULL);
		}
		env_lst_add_back(&copy, node_copy);
		cur = cur->next;
	}
	return (copy);
}
