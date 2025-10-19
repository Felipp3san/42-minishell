/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:38:10 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/18 21:45:12 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>

t_token	*token_lst_new(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->previous = NULL;
	return (token);
}

t_token	*token_lst_last(t_token *token)
{
	while (token && token->next != NULL)
		token = token->next;
	return (token);
}

void	token_lst_add_back(t_token **token_list, t_token *new_token)
{
	t_token	*last_token;

	if (!token_list || !new_token)
		return ;
	if (*token_list == NULL)
	{
		*token_list = new_token;
		new_token->previous = NULL;
		return ;
	}
	last_token = token_lst_last(*token_list);
	last_token->next = new_token;
	new_token->previous = last_token;
}

size_t	token_lst_size(t_token *token)
{
	size_t	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

void	token_lst_clear(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = *token;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*token = NULL;
}
