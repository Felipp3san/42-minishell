/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:32:14 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/11 16:06:38 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./internal_helpers.h"

int	split_assignment(const char *variable, char **out_name, char **out_value)
{
	char	*sign;
	size_t	name_len;

	if (!variable || !out_name || !out_value)
		return (ERROR);
	sign = ft_strchr(variable, '=');
	if (!sign)
	{
		*out_name = ft_strdup(variable);
		if (!*out_name)
			return (ERR_MALLOC);
		*out_value = NULL;
		return (SUCCESS);
	}
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

int	is_valid_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (ERROR);
	if (name[0] != '_' && !ft_isalpha(name[0]))
		return (ERROR);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

/*int insert_in_list(t_env **env, t_env *new_node)
{
    t_env **cur = env;

    while (*cur && name_cmp((char *)(*cur)->content, (char *)new_node->content) < 0)
        cur = &(*cur)->next;
    new_node->next = *cur;
    *cur = new_node;
    return (SUCCESS);
}*/
int insert_in_list(t_env **env, t_env *new_node)
{
    t_env *prev = NULL;
    t_env *cur = NULL;

    if (!env || !new_node)
        return (ERROR);
    cur = *env;
    while (cur && name_cmp((char *)cur->content, (char *)new_node->content) < 0)
    {
        prev = cur;
        cur = cur->next;
    }
    new_node->next = cur;
    new_node->prev = prev;
    if (prev)
        prev->next = new_node;
    else
        *env = new_node;
    if (cur)
        cur->prev = new_node;
    return (SUCCESS);
}
