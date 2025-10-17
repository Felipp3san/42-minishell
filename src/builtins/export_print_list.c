/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:57:54 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/17 12:49:39 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "env.h"
#include "types.h"

static void	print_exp_value(char *value)
{
	const char	*p;

	if (!value)
		return ;
	ft_putchar_fd('"', 1);
	p = value;
	while (*p)
	{
		if (*p == '"' || *p == '\\')
			ft_putchar_fd('\\', 1);
		ft_putchar_fd(*p, 1);
		p++;
	}
	ft_putchar_fd('"', 1);
}

static void	print_exp_list(t_env *exp_list)
{
	while (exp_list)
	{
		if (!exp_list->name)
		{
			exp_list = exp_list->next;
			continue ;
		}
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(exp_list->name, 1);
		if (exp_list->value)
		{
			ft_putchar_fd('=', 1);
			print_exp_value(exp_list->value);
		}
		ft_putchar_fd('\n', 1);
		exp_list = exp_list->next;
	}
}

int	export_print_list(t_env **env)
{
	t_env	*new_list;

	new_list = copy_env_list(*env);
	if (!new_list)
		return (ERR_MALLOC);
	sort_exp_list(new_list);
	print_exp_list(new_list);
	env_lst_clear(&new_list);
	return (SUCCESS);
}
