/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 19:57:54 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/13 19:57:54 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./internal_helpers.h"
#include "builtins.h"
#include "env.h"

int	export_print_list(t_env **env)
{
	t_env	*new_list;

	new_list = copy_env_list(*env);
	if (!new_list)
		return (ERR_MALLOC);
	sort_exp_list(new_list);
	env_lst_print(new_list);
	env_lst_clear(&new_list);
	return (SUCCESS);
}
