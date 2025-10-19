/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 10:42:04 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:10:13 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_err_heredoc(const char *delimiter)
{
	ft_dprintf(2, "minishell: warning:"
		"here-document delimited by end-of-file: wanted(`%s')\n",
		delimiter);
}
