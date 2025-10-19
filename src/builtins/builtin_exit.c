/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:30:19 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 23:00:49 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include "utils.h"

int	get_error_code(char *arg, t_bool *error)
{
	long long	error_code;
	char		*out;

	error_code = ft_strtoll(arg, &out, 10);
	if (ft_strcmp(arg, out) == 0)
		*error = TRUE;
	if (errno == ERANGE)
		*error = TRUE;
	return (error_code);
}

int	builtin_exit(t_command *cmd, t_shell *shell)
{
	const char		*num_req = "numeric argument required";
	const char		*many_args = "too many arguments";
	unsigned char	error_code;
	t_bool			error;

	error = FALSE;
	error_code = shell->last_exit_code;
	if (cmd_lst_size(shell->commands) <= 1)
		ft_putendl_fd("exit", 1);
	if (cmd && cmd->argv && cmd->argv[1])
	{
		if (ft_strcmp(cmd->argv[1], "--") == 0)
			argv_remove_index(cmd, 1);
		if (cmd->argv[2])
			return (print_error_return("exit", many_args, 1));
		if (cmd->argv[1])
		{
			error_code = get_error_code(cmd->argv[1], &error);
			if (error)
				return (print_error_return("exit", num_req, 2));
		}
	}
	exit_shell(shell, error_code);
	return (error_code);
}
