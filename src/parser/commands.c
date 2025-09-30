/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:40:25 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 14:59:33 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_commands	*commands_append(t_commands **lst, t_command *comm)
{
	t_commands	*node;

	node = ft_lstnew((void *) comm);
	if (!node)
		return (NULL);
	ft_lstadd_back(lst, node);
	return (node);
}

void commands_free(t_commands **lst)
{
	ft_lstclear(lst, command_free);
	lst = NULL;
}
