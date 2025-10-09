/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:29:07 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 12:20:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
# define TOKENIZER_INTERNAL_H

# include "tokenizer.h"
# include "types.h"
# include <stddef.h>

// tokenizer_list.c
t_token	*token_lst_new(char *value, t_token_type type);
t_token	*token_lst_last(t_token *token);
void	token_lst_add_back(t_token **token_list, t_token *new_token);
void	token_lst_clear(t_token **token);
size_t	token_lst_size(t_token *token);

// tokenizer_utils.c
t_bool	has_open_quotes(const char *str);
void	advance_to_next_quote(char	**line);
void	skip_spaces(char **line);

// tokenizer_is.c
t_bool	is_space(char ch);
t_bool	is_single_quote(char ch);
t_bool	is_double_quote(char ch);
t_bool	is_separator(char ch);

#endif
