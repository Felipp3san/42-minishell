/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort_exp_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 20:01:42 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/13 20:01:42 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <string.h>
#include "./internal_helpers.h"
#include "builtins.h"
#include "env.h"

static void	swap_content(t_env *a, t_env *b)
{
	char	*tmp_name;
	char	*tmp_value;

	tmp_name = a->name;
	a->name = b->name;
	b->name = tmp_name;
	tmp_value = a->value;
	a->value = b->value;
	b->value = tmp_value;
}

int	check_cmp(t_env *cur)
{
	char	*a;
	char	*b;
	int		cmp;

	a = cur->name;
	b = cur->next->name;
	if (!a && !b)
		cmp = 0;
	else if (!a)
		cmp = -1;
	else if (!b)
		cmp = 1;
	else
		cmp = ft_strcmp(a, b);
	return (cmp);
}

int	sort_exp_list(t_env *head)
{
	bool	swapped;
	t_env	*cur;
	int		cmp;

	if (!head)
		return (ERROR);
	swapped = true;
	while (swapped)
	{
		swapped = false;
		cur = head;
		while (cur && cur->next)
		{
			cmp = check_cmp(cur);
			if (cmp > 0)
			{
				swap_content(cur, cur->next);
				swapped = true;
			}
			cur = cur->next;
		}
	}
	return (SUCCESS);
}
