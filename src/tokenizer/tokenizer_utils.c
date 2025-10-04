/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:41:34 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 19:09:58 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "tokenizer_internal.h"

t_bool	ch_is_operator(char ch)
{
	return (ch == '>' || ch == '<' || ch == '|');
}

t_bool	ch_is_space(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == ' ');
}

t_bool	ch_is_single_quote(char ch)
{
	return (ch == '\'');
}

t_bool	ch_is_double_quote(char ch)
{
	return (ch == '\"');
}

t_bool	has_open_quotes(const char *str)
{
	t_bool	single_opened;
	t_bool	double_opened;

	single_opened = FALSE;
	double_opened = FALSE;
	while (*str)
	{
		if (ch_is_single_quote(*str) && !double_opened)
			single_opened = !single_opened;
		if (ch_is_double_quote(*str) && !single_opened)
			double_opened = !double_opened;
		str++;
	}
	return (single_opened || double_opened);
}
