/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:08 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 19:28:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"

static int	is_option_n(char *s)
{
	int	i;

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

int	builtin_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (!args || !*args)
		return (ERROR);
	while (args[i] && is_option_n(args[i]) == SUCCESS)
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (SUCCESS);
}
