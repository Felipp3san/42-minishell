/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:30:19 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 15:15:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"
#include "parser.h"

int	get_error_code(char *arg, t_bool *error)
{
	long long	error_code;
	char		*out;

	error_code = ft_strtoll(arg, &out, 10);
	if (ft_strcmp(arg, out) == 0)
		*error = TRUE;
	if (error_code < 0)
		return (0);
	else
		return (error_code);
}

int	builtin_exit(char **args, t_shell *shell)
{
	unsigned char	error_code;
	t_bool			error;

	error = FALSE;
	error_code = 0;
	if (cmd_lst_size(shell->commands) <= 1)
		ft_putendl_fd("exit", 1);
	if (!args || !args[1])
		error_code = g_last_exit_code;
	else
	{
		if (args[2])
		{
			print_error("exit", "too many arguments", 0);
			return (2);
		}
		else if (args[1])
		{
			error_code = get_error_code(args[1], &error);
			if (error)
			{
				print_error("exit", "numeric argument required", 0);
				return (2);
			}
		}
	}
	exit_shell(shell, error_code);
	return (2);
}
