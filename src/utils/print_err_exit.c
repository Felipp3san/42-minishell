/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:27:15 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 21:30:07 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_strs(char *s1, const char *s2)
{
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

int	print_err_exit(const char *cmd_name, const char *msg, int exit_code)
{
	char	*shell_name;
	char	*full_msg;

	shell_name = ft_strdup("minishell");
	full_msg = join_strs(shell_name, ": ");
	full_msg = join_strs(full_msg, cmd_name);
	full_msg = join_strs(full_msg, ": ");
	full_msg = join_strs(full_msg, msg);
	ft_putendl_fd(full_msg, 2);
	free (full_msg);
	return (exit_code);
}
