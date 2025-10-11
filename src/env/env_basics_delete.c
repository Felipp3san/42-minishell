/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_basics_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 15:45:47 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/11 15:45:47 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "../builtins/env_helpers/internal_helpers.h"

// ----------------------
// 1. Delete a node by content prefix
// ----------------------
int env_delete(t_env **head, const char *name)
{
    t_env *node;

	if (!head || !name)
		return (ERROR);
	node = search_variable(*head, (char *)name);
    if (!node)
        return (SUCCESS);
    if (node->prev)
        node->prev->next = node->next;
    else
        *head = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node->content);
    free(node);
	return (SUCCESS);
}

// ----------------------
// 2. Free the entire list
// ----------------------
void	env_free_all(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next;
	}
	*env = NULL;
}

// ----------------------
// 3. Count the the number of nodes of the list
// ----------------------
int	env_size(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
