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

typedef enum	s_quote
{
	UNSET,
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_quote;

typedef struct	s_token
{
	char		*str;
	int			type;
	t_quote		quote;
	t_bool		preceded_by_space;
}	t_token;

// tokens.c
t_token	*token_new(char *str);
void	token_free(void *content);

#endif
