/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:28:03 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/10 13:55:46 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include <stdlib.h>
#include <unistd.h>

t_redir	*redir_lst_new(char *value, int heredoc_fd, t_token_type type) {
	t_redir	*redir;

	redir = (t_redir *) malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->value = value;
	redir->heredoc_fd = heredoc_fd;
	redir->type = type;
	redir->next = NULL;
	redir->previous = NULL;
	return (redir);
}

t_redir	*redir_lst_last(t_redir *redir)
{
	while (redir && redir->next != NULL)
		redir = redir->next;
	return (redir);
}

void	redir_lst_add_back(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*last_redir;

	if (!redir_list || !new_redir)
		return ;
	if (*redir_list == NULL)
	{
		*redir_list = new_redir;
		new_redir->previous = NULL;
		return ;
	}
	last_redir = redir_lst_last(*redir_list);
	last_redir->next = new_redir;
	new_redir->previous = last_redir;
}

size_t	redir_lst_size(t_redir *redir)
{
	size_t	count;

	count = 0;
	if (!redir)
		return (count);
	if (redir)
	{
		count++;
		redir = redir->next;
	}
	return (count);
}

void	redir_lst_clear(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	if (!redir)
		return ;
	current = *redir;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		if (current->heredoc_fd != -1)
			close(current->heredoc_fd);
		free(current);
		current = next;
	}
	*redir = NULL;
}
