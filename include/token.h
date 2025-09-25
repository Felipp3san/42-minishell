/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:15:59 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 18:27:49 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include <stddef.h>

typedef	struct s_token
{
	char	**tokens;
	size_t	count;
}	t_token;

void	free_tokens(t_token *tok);
int		tokens_init(t_token *tok);
int		realloc_tokens(t_token *tok);
int		tokens_append(t_token *tok, char *str);

#endif
