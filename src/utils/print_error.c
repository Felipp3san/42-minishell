/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:30:40 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 15:34:45 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	print_error(const char *cmd_name, const char *msg, char *optional)
{
	char	*full_msg;

	full_msg = ft_strjoin_free(ft_strdup("minishell: "), NULL);
	full_msg = ft_strjoin_free(full_msg, ft_strdup(cmd_name));
	full_msg = ft_strjoin_free(full_msg, ft_strdup(": "));
	full_msg = ft_strjoin_free(full_msg, ft_strdup(msg));
	if (optional)
	{
		full_msg = ft_strjoin_free(full_msg, ft_strdup(": "));
		full_msg = ft_strjoin_free(full_msg, ft_strdup(optional));
	}
	ft_putendl_fd(full_msg, STDERR_FILENO);
	free(full_msg);
}

int	print_error_return(const char *cmd_name, const char *msg, int code)
{
	print_error(cmd_name, msg, 0);
	return (code);
}
