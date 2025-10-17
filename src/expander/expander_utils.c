/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:15:28 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 20:00:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"

int		is_valid_var_char(char ch)
{
	if (ft_isalnum(ch) || ch == '_')
		return (TRUE);
	return (FALSE);
}

