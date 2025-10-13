/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:29:07 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 12:08:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
# define TOKENIZER_INTERNAL_H

# include <stddef.h>
# include "token.h"

// tokenizer_list.c
t_token	*token_lst_new(char *value, t_token_type type);
t_token	*token_lst_last(t_token *token);
void	token_lst_add_back(t_token **token_list, t_token *new_token);
void	token_lst_clear(t_token **token);
size_t	token_lst_size(t_token *token);

// tokenizer_utils.c
int		has_open_quotes(const char *str);
void	advance_to_next_quote(char	**line);
void	skip_spaces(char **line);

#endif
