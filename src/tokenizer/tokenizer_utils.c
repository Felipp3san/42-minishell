/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:41:34 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 11:42:54 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_operator(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (TRUE);
	else
		return (FALSE);
}

t_bool	is_space(char ch)
{
	if (ch == ' ')
		return (TRUE);
	else
		return (FALSE);
}

t_bool	is_single_quote(char ch)
{
	if (ch == '\'')
		return (TRUE);
	else
		return (FALSE);
}

t_bool	is_double_quote(char ch)
{
	if (ch == '\"')
		return (TRUE);
	else
		return (FALSE);
}

