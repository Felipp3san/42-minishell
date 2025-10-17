/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:04:06 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:40:08 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

static size_t	size_without_quotes(const char *str)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (!is_single_quote(str[i]) && !is_double_quote(str[i]))
			size++;
		i++;
	}
	return (size);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!(*str))
		return (NULL);
	size = size_without_quotes(str);
	new_str = (char *) malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_single_quote(str[i]) && !is_double_quote(str[i]))
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}
