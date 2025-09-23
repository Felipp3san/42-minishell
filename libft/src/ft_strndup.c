/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:15:04 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/23 16:21:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup_str;
	size_t	src_size;
	size_t	i;

	src_size = ft_strlen(s);
	if (n > src_size)
		n = src_size;
	dup_str = (char *) malloc (n + 1);
	if (!dup_str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(dup_str + i) = *(s + i);
		i++;
	}
	*(dup_str + i) = '\0';
	return (dup_str);
}
