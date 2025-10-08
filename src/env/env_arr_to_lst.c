/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr_to_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:25:42 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 19:25:43 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*env_arr_to_lst(char **envp)
{
	t_list	*clone;
	t_list	*node;
	char	*content;
	size_t	i;

	if (!envp)
		return (NULL);
	clone = NULL;
	i = 0;
	while (envp[i])
	{
		content = ft_strdup(envp[i]);
		if (!content)
			return (ft_lstclear(&clone, free), NULL);
		node = ft_lstnew(content);
		if (!node)
		{
			free(content);
			return (ft_lstclear(&clone, free), NULL);
		}
		ft_lstadd_back(&clone, node);
		i++;
	}
	return (clone);
}
