/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:11:09 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 14:17:07 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "token.h"

// tokenizer.c
t_token	*tokenize(char *line);
t_token	*token_lst_last(t_token *token);
void	token_lst_clear(t_token **token);

#endif
