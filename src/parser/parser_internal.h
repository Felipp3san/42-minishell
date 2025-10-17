/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:40:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 11:21:50 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "token.h"

// parser_heredoc.c
int		parser_heredoc(char *delimiter);

// parser_utils.c
char	*get_redir_value(char *token_value, int *expand);
t_token	*syntax_check(t_token *token);
void	print_parser_err(t_token *error);

// parser_is.c
int		is_redir(t_token_type type);
int		is_sep(t_token_type type);
int		is_word(t_token_type type);
int		is_heredoc(t_token_type type);

#endif
