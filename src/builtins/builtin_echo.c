/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:08 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/04 17:38:22 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"

static int	is_option_n(char *s)
{
	int i;

	if (!s || s[0] != '-')
		return (ERROR);
	i = 1;
	if (s[i] == '\0')
		return (ERROR);
	while (s[i])
	{
		if (s[i] != 'n')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	builtin_echo(char **args, int fd)
{
	int i;
	int	newline;

	i = 0;
	newline = 1;
	if (!args || !*args || fd <= 0)
		return (ERROR);
	while (args[i] && is_option_n(args[i]) == SUCCESS)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (newline)
		write(fd, "\n", 1);
	return (SUCCESS);
}
