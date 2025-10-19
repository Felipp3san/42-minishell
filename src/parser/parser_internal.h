/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:40:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:11:04 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "token.h"

// parser_utils.c
t_token	*syntax_check(t_token *token);
void	print_parser_err(t_token *error);
char	*remove_quotes(char *str);
int		should_expand_heredoc(char *value);

// parser_is.c
int		is_redir(t_token_type type);
int		is_sep(t_token_type type);
int		is_word(t_token_type type);

#endif
