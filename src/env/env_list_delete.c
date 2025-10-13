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
#include "types.h"

// ----------------------
// 1. Delete a node by content prefix
// ----------------------
int env_var_delete(t_env **head, const char *name)
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
    free(node->name);
	free(node->value);
    free(node);
	return (SUCCESS);
}

// ----------------------
// 2. Free the entire list
// ----------------------
void	env_lst_clear(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (!env)
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		if (current->name)
		{
			free(current->name);
			if (current->value)
				free(current->value);
		}
		free(current);
		current = next;
	}
	*env = NULL;
}

// ----------------------
// 3. Return last node
// ----------------------
t_env	*env_lst_last(t_env *head)
{
	while (head && head->next != NULL)
		head = head->next;
	return (head);
}
