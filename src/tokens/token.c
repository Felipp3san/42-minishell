/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 00:31:12 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 00:33:22 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"
#include "libft.h"

t_token	*token_create(const char *str, t_quote quote)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strdup(str);
	token->quote = quote;
	return (token);
}
