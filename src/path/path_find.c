/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:25:59 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:40:17 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "path.h"
#include "utils.h"
#include "env.h"

/* Looks for the command in the system, using paths extracted from the PATH 
 * variable from envp, or return it directly if cmd is a fullpath */
char	*path_find(const char *cmd, char **envp)
{
	char	**paths;
	char	*path_var;
	char	*full_path;
	size_t	i;

	if (!cmd)
		cmd = " ";
	if (ft_strchr(cmd, '/'))
		return ((char *)cmd);
	path_var = env_get_arr(envp, "PATH");
	if (!path_var)
		return (NULL);
	paths = path_split(path_var);
	i = 0;
	while (paths && paths[i])
	{
		full_path = path_join(paths[i], cmd);
		if (!full_path)
			return (free_split(paths), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (free_split(paths), NULL);
}
