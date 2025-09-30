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
# include <types.h>

typedef struct s_list t_tokens;

typedef enum	s_quote
{
	UNSET,
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote;

typedef struct	s_token
{
	char	*str;
	t_quote	type;
}	t_token;

// tokens.c
t_token		*token_new(char *str);
t_tokens	*token_append(t_tokens **lst, t_token *token);
void		token_free(void *content);
void		tokens_free(t_tokens **lst);

#endif
