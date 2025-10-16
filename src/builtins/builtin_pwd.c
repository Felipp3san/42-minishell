/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/16 17:25:20 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include <stdlib.h>

int	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (ERROR);
	if (write(1, path, ft_strlen(path)) == -1
		|| write(1, "\n", 1) == -1)
	{
		free(path);
		return (ERROR);
	}
	free(path);
	return (SUCCESS);
}
