/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 09:36:34 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"

int	builtin_env()
{
	if (!env)
		return (SUCCESS);
	while (env != NULL)
	{
		if (ft_strchr((char *)env->content, '='))
			ft_putendl_fd((char *)env->content, 1);
		env = env->next;
	}
	return (SUCCESS);
}
