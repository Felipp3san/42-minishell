/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                           .:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:14:21 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 00:35:21 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdlib.h>

t_token	*token_new(char *str)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = UNSET;
	token->quote = UNSET;
	return (token);
}

void token_free(void *content)
{
	if (!content)
		return ;
	free(content);
}
