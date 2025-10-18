/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:32:14 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/18 00:07:34 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "types.h"

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

static int	get_only_name(const char *var, char **out_name, char **out_value)
{
	*out_name = ft_strdup(var);
	if (!*out_name)
		return (ERR_MALLOC);
	*out_value = NULL;
	return (SUCCESS);
}

int	split_assignment(const char *variable, char **out_name, char **out_value)
{
	char	*sign;
	size_t	name_len;

	if (!variable || !out_name || !out_value)
		return (ERROR);
	sign = ft_strchr(variable, '=');
	if (!sign)
		return (get_only_name(variable, out_name, out_value));
	name_len = (size_t)(sign - variable);
	if (name_len == 0)
		return (ERROR);
	*out_name = malloc((name_len + 1) * sizeof(char));
	if (!*out_name)
		return (ERR_MALLOC);
	ft_strlcpy(*out_name, variable, name_len + 1);
	*out_value = ft_strdup(sign + 1);
	if (!*out_value)
	{
		free(*out_name);
		*out_name = NULL;
		return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	is_valid_name(char *name, int *plus)
{
	int	i;

	if (!name || !name[0])
		return (ERROR);
	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (ERROR);
	i = 1;
	while (name[i])
	{
		if (name[i] == '+' && name[i + 1] == '\0')
		{
			*plus = 1;
			i++;
			continue ;
		}
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
