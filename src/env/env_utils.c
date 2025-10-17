/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:32:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 22:42:35 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "../builtins/env_helpers/internal_helpers.h"
#include "types.h"

int	env_var_delete(t_env **head, const char *name)
{
	t_env	*node;

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

void	env_arr_free(char **envp)
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

void	env_lst_print(t_env *head)
{
	while (head)
	{
		if (head->value)
		{
			ft_putstr_fd(head->name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(head->value, 1);
		}
		head = head->next;
	}
}
