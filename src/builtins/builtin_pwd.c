/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:35:09 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "libft.h"
#include <stdlib.h>

int	write_pwd(char *s, int fd)
{
	ssize_t	len;
	ssize_t	w;

	if (!s)
		return (ERROR);
	len = (ssize_t)ft_strlen(s);
	w = write(fd, s, len);
	if (w != len)
		return (ERROR);
	w = write(fd, "\n", 1);
	if (w != 1)
		return (ERROR);
	return (SUCCESS);
}

int	builtin_pwd(int fd)
{
	char	*path;

	if (fd < 0)
		return (ERROR);
	path = getcwd(NULL, 0);
	if (!path)
		return (ERROR);
	if (write_pwd(path, fd) < 0)
	{
		free(path);
		return (ERROR);
	}
	free(path);
	return (SUCCESS);
}
