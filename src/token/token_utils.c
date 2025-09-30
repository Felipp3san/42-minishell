/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:29:47 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 15:30:02 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

char	*get_token_value(t_token *token)
{
	if (!token || !token->str)
		return (NULL);
	return (token->str);
}

