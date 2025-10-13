/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 12:06:53 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 12:07:15 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_separator(char ch)
{
	return (ch == '>' || ch == '<' || ch == '|');
}

int	is_space(char ch)
{
	return ((ch >= 9 && ch <= 13) || ch == ' ');
}

int	is_single_quote(char ch)
{
	return (ch == '\'');
}

int	is_double_quote(char ch)
{
	return (ch == '\"');
}
