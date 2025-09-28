/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:41:34 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/27 22:10:47 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

t_bool	is_operator(char ch)
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
