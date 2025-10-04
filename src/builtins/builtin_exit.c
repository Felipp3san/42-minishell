/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:42:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/03 18:24:31 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "utils.h"

int	get_error_code(char *arg, t_bool error)
{
	int	i;
	int	error_code;

	i = 0;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] && !ft_isdigit(arg[i]))
	{
		error = TRUE;
		return (error_code);
	}
	error_code = ft_atoll(arg);
	return (error_code);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	long long	error_code;
	t_bool		error;

	error = FALSE;
	error_code = 0;
	if (!argv || !argv[1])
		error_code = shell->last_exit_status;
	else
	{
		if (argv[2])
		{
			print_error("exit", "too many arguments");
			return (ERROR);
		}
		else if (argv[1])
		{
			error_code = get_error_code(argv[1], &error);
			if (error)
				print_error("exit", "numeric argument required");
			error_code = error_code % 255;
		}
	}
	return (error_code);
}
