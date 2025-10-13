/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 18:16:03 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include "env.h"

int	builtin_env(t_env *env)
{
<<<<<<< HEAD
	env_lst_print(env);
=======
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
>>>>>>> origin/main
	return (SUCCESS);
}
