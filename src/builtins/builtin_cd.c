/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/16 18:30:30 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "utils.h"
#include <string.h>
#include "builtins.h"

static int	update_env_oldpwd(t_env **env, const char *oldcwd)
{
	char	*oldpwd_str;

	if (!oldcwd)
		return (ERROR);
	oldpwd_str = ft_strjoin("OLDPWD=", oldcwd);
	if (!oldpwd_str)
		return (ERR_MALLOC);
	builtin_export(env, oldpwd_str);
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
	builtin_export(env, tmp);
	free(cwd);
	free(tmp);
	return (SUCCESS);
}

int	builtin_cd(char **args, t_env **env)
{
	char	*target;
	char	oldcwd[PATH_MAX];

	if (!args || args[2])
		return (print_err_exit("cd", "too many arguments", 2));
	if (!args[1])
	{
		target = getenv("HOME");
		if (!target)
			return (ERROR);
	}
	else
		target = args[1];
	if (!getcwd(oldcwd, PATH_MAX))
		return (ERROR);
	if (chdir(target) != 0)
	{
		print_error("cd", target, strerror(errno));
		return (EXIT_FAILURE);
	}
	if (update_env_oldpwd(env, oldcwd) != SUCCESS)
		return (ERROR);
	if (update_env_pwd(env) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
