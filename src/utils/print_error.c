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

#include "libft.h"
#include <unistd.h>

static char	*join_strs(char *s1, const char *s2)
{
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

void	print_error(const char *cmd_name, const char *msg, const char *optional)
{
	char	*shell_name;
	char	*full_msg;

	shell_name = ft_strdup("minishell");
	full_msg = join_strs(shell_name, ": ");
	full_msg = join_strs(full_msg, cmd_name);
	full_msg = join_strs(full_msg, ": ");
	full_msg = join_strs(full_msg, msg);
	if (optional)
	{
		full_msg = join_strs(full_msg, ": ");
		full_msg = join_strs(full_msg, optional);
	}
	ft_putendl_fd(full_msg, STDERR_FILENO);
	free (full_msg);
}
