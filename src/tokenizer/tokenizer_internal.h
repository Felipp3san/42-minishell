/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:29:07 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 11:06:18 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_INTERNAL_H
# define TOKENIZER_INTERNAL_H

# include <stddef.h>

// tokenizer_utils.c
int		has_open_quotes(const char *str);
void	advance_to_next_quote(char	**line);
void	skip_spaces(char **line);

#endif
