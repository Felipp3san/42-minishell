/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 12:42:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:35:58 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "utils.h"

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

int	builtin_exit(char **argv, t_shell *shell)
{
	unsigned char	error_code;
	t_bool			error;

	error = FALSE;
	error_code = 0;
	if (!argv || !argv[1])
		error_code = shell->last_exit_status;
	else
	{
		if (argv[2])
		{
			print_error("exit", "too many arguments", 0);
			return (ERROR);
		}
		else if (argv[1])
		{
			error_code = get_error_code(argv[1], &error);
			if (error)
			{
				print_error("exit", "numeric argument required", 0);
				return (ERROR);
			}
		}
	}
	return (error_code);
}
