/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:01:12 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/29 17:01:21 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <types.h>
#include "tokenizer.h"

t_bool	has_open_quotes(const char *str)
{
	char	ch;
	t_state	mode;
	t_bool	single_opened;
	t_bool	double_opened;

	mode = NORMAL;
	single_opened = FALSE;
	double_opened = FALSE;
	while (*str)
	{
		ch = *str;
		if (is_single_quote(ch) && (mode != DOUBLE))
		{
			if (single_opened == TRUE)
			{
				mode = NORMAL;
				single_opened = FALSE;
			}
			else
			{
				mode = SINGLE;
				single_opened = TRUE;
			}
		}
		if (is_double_quote(ch) && (mode != SINGLE))
		{
			if (double_opened == TRUE)
			{
				mode = NORMAL;
				double_opened = FALSE;
			}
			else
			{
				mode = DOUBLE;
				double_opened = TRUE;
			}
		}
		str++;
	}
	return (single_opened || double_opened);
}
