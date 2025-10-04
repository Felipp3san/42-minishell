/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:29:07 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 18:59:30 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
# define TOKENIZER_INTERNAL_H

# include "libft.h"
# include "buffer.h"
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
	t_buffer	*buffer;
	t_state		state;
	char		ch;
	t_status	err;
}	t_tokenizer;

// tokenizer.c
t_status	add_token(t_buffer *buffer, t_list **out);

// tokenizer_modes.c
int			normal_mode(t_tokenizer *tok, t_list **out);
int			single_mode(t_tokenizer *tok);
int			double_mode(t_tokenizer *tok);
int			operator_mode(t_tokenizer *tok, t_list **out);

// tokenizer_utils.c
t_bool		ch_is_space(char ch);
t_bool		ch_is_single_quote(char ch);
t_bool		ch_is_double_quote(char ch);
t_bool		ch_is_operator(char ch);

#endif
