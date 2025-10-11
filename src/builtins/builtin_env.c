/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 11:09:13 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"

int	builtin_env(t_list *env)
{
	t_list	*lst;
	char	*print;

	lst = env;
	print = NULL;
	while (lst)
    {
		print = (char *)lst->content;
        ft_putendl_fd(print, 1);
        lst = lst->next;
    }
	return (SUCCESS);
}
