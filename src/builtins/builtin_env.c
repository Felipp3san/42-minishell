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
<<<<<<< HEAD
	env_lst_print(env);
=======
=======
>>>>>>> 271923ab8ee629414d01f93a8ff230c634abff05
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
<<<<<<< HEAD
>>>>>>> origin/main
=======
>>>>>>> 271923ab8ee629414d01f93a8ff230c634abff05
	return (SUCCESS);
}
