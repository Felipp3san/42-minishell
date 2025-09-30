/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:14:21 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 14:59:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "libft.h"

t_tokens	*token_append(t_tokens **lst, t_token *token)
{
	t_tokens	*node;

	node = ft_lstnew((void *) token);
	if (!node)
		return (NULL);
	ft_lstadd_back(lst, node);
	return (node);
}

t_token	*token_new(char *str)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	return (token);
}

void token_free(void *token)
{
	if (!token)
		return ;
	if (((t_token *) token)->str)
		free(((t_token *) token)->str);
	free(token);
}

void tokens_free(t_tokens **lst)
{
	ft_lstclear(lst, token_free);
	lst = NULL;
}
