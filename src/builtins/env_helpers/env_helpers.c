/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:39:07 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/16 17:27:40 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./internal_helpers.h"

static size_t	get_content_len(const char *sign, const char *content)
{
	if (sign)
		return ((size_t)(sign - content));
	else
		return (ft_strlen(content));
}

int	name_cmp(const char *a, const char *b)
{
	const char	*a_sign;
	const char	*b_sign;
	size_t		a_len;
	size_t		b_len;
	int			res;

	a_sign = ft_strchr(a, '=');
	b_sign = ft_strchr(b, '=');
	a_len = get_content_len(a_sign, a);
	b_len = get_content_len(b_sign, b);
	if (a_len < b_len)
		res = ft_strncmp(a, b, a_len);
	else
		res = ft_strncmp(a, b, b_len);
	if (res != 0)
		return (res);
	if (a_len < b_len)
		return (-1);
	if (a_len > b_len)
		return (1);
	return (0);
}
