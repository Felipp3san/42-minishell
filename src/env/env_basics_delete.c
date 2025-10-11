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

// ----------------------
// 1. Delete a node by content prefix
// ----------------------
void env_delete(t_env **head, const char *prefix)
{
    t_env *node;

	node = env_find(*head, prefix);
    if (!node)
        return;
    if (node->previous)
        node->previous->next = node->next;
    else
        *head = node->next; // node was head
    if (node->next)
        node->next->previous = node->previous;
    free(node->content);
    free(node);
}

// ----------------------
// 2. Free the entire list
// ----------------------
void env_free_all(t_env *head)
{
    t_env *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->content);
        free(tmp);
    }
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
