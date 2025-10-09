/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_is.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 12:17:42 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 12:17:53 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_bool	is_separator(char ch)
{
	return (ch == '>' || ch == '<' || ch == '|');
}

t_bool	is_space(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == ' ');
}

t_bool	is_single_quote(char ch)
{
	return (ch == '\'');
}

t_bool	is_double_quote(char ch)
{
	return (ch == '\"');
}
