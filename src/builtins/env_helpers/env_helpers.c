/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:39:07 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/12 19:25:20 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./internal_helpers.h"

static void	compute_name_value_len(const char *content, const char *value,
	int *name_len, int *value_len)
{
	char	*sign;

	sign = ft_strchr(content, '=');
	if (sign)
		*name_len = sign - content;
	else
		*name_len = ft_strlen(content);
	if (value)
		*value_len = ft_strlen(value);
	else
		*value_len = 0;
}

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

char	*build_new_var_string(const char *content, const char *value)
{
	int		name_len;
	int		value_len;
	char	*new_str;

	compute_name_value_len(content, value, &name_len, &value_len);
	if (value_len > 0)
		new_str = malloc(name_len + 1 + value_len + 1);
	else
		new_str = malloc(name_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, content, name_len);
	if (value_len > 0)
	{
		new_str[name_len] = '=';
		ft_memcpy(new_str + name_len + 1, value, value_len);
		new_str[name_len + 1 + value_len] = '\0';
	}
	else
		new_str[name_len] = '\0';
	return (new_str);
}
