/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:59:58 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/14 18:13:16 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "env.h"

// ----------------------
// 1. Create a new node
// ----------------------
t_env *env_lst_new(char *name, char *value)
{
    t_env *node;

    node= malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->name = name;
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return (node);
}

// ----------------------
// 2. Append node to list
// ----------------------
void env_lst_add_back(t_env **head, t_env *new_node)
{
    t_env *tmp;

    if (!head || !new_node)
        return;
    if (*head == NULL)
    {
        *head = new_node;
        new_node->prev  = NULL;
        return ;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
}

// ----------------------
// 3. Print the list
// ----------------------
void env_lst_print(t_env *head)
{
    while (head)
    {
		if(head->value)
		{
        	ft_putstr_fd(head->name, 1);
        	ft_putchar_fd('=', 1);
       		ft_putendl_fd(head->value, 1);
		}
        head = head->next;
    }
}

// ----------------------
// 4. Prepend node to the list
// ----------------------
void env_lst_add_front(t_env **head, t_env *new_node)
{
    if (!head || !new_node)
        return;

    new_node->next = *head;
    new_node->prev = NULL;
    if (*head)
        (*head)->prev = new_node;
    *head = new_node;
}

// ----------------------
// 5. Count the the number of nodes of the list
// ----------------------
int	env_lst_size(t_env *head)
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
