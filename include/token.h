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

typedef	struct s_tokens
{
	char	**tokens;
	size_t	size;
	size_t	capacity;
}	t_tokens;

int		tokens_init(t_tokens *tok);
int		tokens_realloc(t_tokens *tok);
int		tokens_append(t_tokens *tok, char const *str);
void	tokens_free(t_tokens *tok);

#endif
