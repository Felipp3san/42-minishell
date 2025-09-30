/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:11:09 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 14:13:18 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "buffer.h"
# include "token.h"
# include "types.h"

typedef enum e_state
{
	NORMAL,
	SINGLE,
	DOUBLE,
	OPERATOR
}	t_state;

typedef struct s_tokenizer
{
	t_buffer	buffer;
	t_state		state;
	char		ch;
	t_status	err;
}	t_tokenizer;

// tokenizer.c
t_status	tokenize(char const *str, t_tokens **out);
t_status	add_token(t_tokens **tokens, t_buffer *buffer);

// tokenizer_modes.c
int			normal_mode(t_tokenizer *tok, t_tokens **tokens);
int			single_mode(t_tokenizer *tok, t_tokens **tokens);
int			double_mode(t_tokenizer *tok, t_tokens **tokens);
int			operator_mode(t_tokenizer *tok, t_tokens **tokens);

// tokenizer_utils.c
t_bool		is_space(char ch);
t_bool		is_single_quote(char ch);
t_bool		is_double_quote(char ch);
t_bool		is_operator(char ch);

#endif
