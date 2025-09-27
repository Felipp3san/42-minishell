/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:11:09 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 22:03:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "types.h"
#include "token.h"
#include "buffer.h"

typedef enum e_state
{
	NORMAL,
	SINGLE,
	DOUBLE,
	OPERATOR
}	t_state;

typedef struct s_tokenizer
{
	t_tokens	*tokens;
	t_buffer	buffer;
	t_state		state;
}	t_tokenizer;

// tokenizer.c
t_tokens	*tokenizer(char const *str);
t_status	add_token(t_tokenizer *tok);
void		free_all(t_tokenizer *tok);

// tokenizer_utils.c
t_bool	is_space(char ch);
t_bool	is_single_quote(char ch);
t_bool	is_double_quote(char ch);
t_bool	is_operator(char ch);

// tokenizer_modes.c
t_status	normal_mode(t_tokenizer *tok, char ch);
t_status	single_mode(t_tokenizer *tok, char ch);
t_status	double_mode(t_tokenizer *tok, char ch);
t_status	operator_mode(t_tokenizer *tok, char ch);

#endif
