/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stroll_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 22:08:31 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/03 22:09:09 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_prefix(const char *ptr, int *base)
{
	if (ft_strncmp(ptr, "0x", 2) == 0)
	{
		*base = 16;
		return (2);
	}
	else if (ft_strncmp(ptr, "0", 1) == 0)
	{
		*base = 8;
		return (1);
	}
	else if (base == 0)
		*base = 10;
	return (0);
}

int	from_base(int base, char ch)
{
	const char arr[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int	i;
	
	i = -1;
	while (++i < base)
	{
		if (ft_tolower(ch) == ft_tolower(arr[i]))
			return (i);
	}
	return (-1);
}
