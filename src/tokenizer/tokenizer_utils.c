/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:41:34 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 12:08:48 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"
#include "libft.h"
#include "utils.h"
#include "types.h"

void	skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
		(*line)++;
}

void	advance_to_next_quote(char	**line)
{
	char	quote;

	quote = **line;
	*line = *line + 1;
	while (**line && (**line != quote))
		(*line)++;
}

int	has_open_quotes(const char *str)
{
	int	single_opened;
	int	double_opened;

	single_opened = FALSE;
	double_opened = FALSE;
	while (*str)
	{
		if (is_single_quote(*str) && !double_opened)
			single_opened = !single_opened;
		if (is_double_quote(*str) && !single_opened)
			double_opened = !double_opened;
		str++;
	}
	return (single_opened || double_opened);
}
