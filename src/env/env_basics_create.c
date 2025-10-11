/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:59:58 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/11 13:59:58 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "env.h"

// ----------------------
// 1. Create a new node
// ----------------------
t_env *env_new(char *content)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    node->content = content;
    if (!node->content)
    {
        free(node);
        return NULL;
    }
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// ----------------------
// 2. Append node to list
// ----------------------
void env_append(t_env **head, t_env *new_node)
{
    t_env *tmp;

    if (!head || !new_node)
        return;
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
    new_node->prev = tmp;
}

// ----------------------
// 3. Find a node by content prefix (e.g., "PATH=")
// ----------------------
t_env *env_find(t_env *head, const char *prefix)
{
    while (head)
    {
        if (ft_strncmp(head->content, prefix, ft_strlen(prefix)) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

// ----------------------
// 4. Print the list (for debugging)
// ----------------------
void env_print(t_env *head)
{
    while (head)
    {
        ft_putendl_fd(head->content, 1);
        head = head->next;
    }
}

// ----------------------
// 5. Prepend node to the list
// ----------------------
void env_prepend(t_env **head, t_env *new_node)
{
    if (!head || !new_node)
        return;

    new_node->next = *head;
    new_node->prev = NULL;

    if (*head)
        (*head)->prev = new_node;

    *head = new_node;
}
