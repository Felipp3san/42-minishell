/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/21 16:50:39 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "libft.h"
#include "types.h"
#include "utils.h"
#include "builtins.h"
#include "env.h"

static int	update_env_oldpwd(t_env **env, const char *oldcwd)
{
	char	*oldpwd_str;

	if (!oldcwd)
		return (ERROR);
	oldpwd_str = ft_strjoin("OLDPWD=", oldcwd);
	if (!oldpwd_str)
		return (ERR_MALLOC);
	process_variable(env, oldpwd_str);
	free(oldpwd_str);
	return (SUCCESS);
}

static int	update_env_pwd(t_env **env)
{
	char	*cwd;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ERROR);
	tmp = ft_strjoin("PWD=", cwd);
	if (!tmp)
	{
		free(cwd);
		return (ERR_MALLOC);
	}
	process_variable(env, tmp);
	free(cwd);
	free(tmp);
	return (SUCCESS);
}

static void	handle_no_dir(char *target, t_env *env)
{
	target = env_get_lst(env, "HOME");
	if (!target)
		target = "/";
	chdir(target);
	print_error(
		"cd",
		"error retrieving current directory: getcwd: "
		"cannot access parent directories",
		strerror(errno)
		);
}

int	builtin_cd(char **args, t_env **env)
{
	char	*target;
	char	oldcwd[PATH_MAX];

	if (!args || (args[1] && args[2]))
		return (print_error_return("cd", "too many arguments", EXIT_FAILURE));
	if (!args[1])
	{
		target = env_get_lst(*env, "HOME");
		if (!target)
			return (ERROR);
	}
	else
		target = args[1];
	if (!getcwd(oldcwd, PATH_MAX))
		oldcwd[0] = '\0';
	if (chdir(target) == 0)
	{
		if (!getcwd(NULL, 0))
			handle_no_dir(target, *env);
	}
	if (update_env_oldpwd(env, oldcwd) != SUCCESS)
		return (ERROR);
	if (update_env_pwd(env) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
