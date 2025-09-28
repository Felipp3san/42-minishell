/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 18:15:59 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/28 00:41:20 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# include <stddef.h>

typedef enum	s_quote
{
	UNSET,
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote;

typedef struct s_token
{
	char	*value;
	t_quote	quote;
}	t_token;

typedef struct s_tokens
{
	t_token	**tokens;
	size_t	size;
	size_t	capacity;
}	t_tokens;

// tokens.c
int		tokens_init(t_tokens *tok);
int		tokens_realloc(t_tokens *tok);
int		tokens_append(t_tokens *tokens, t_token *token);
void	tokens_free(t_tokens *tok);

// token.c
t_token	*token_create(const char *str, t_quote quote);

#endif
