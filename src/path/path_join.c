/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:49:44 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:23:12 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Join the path with the command separated by a slash.
 * Ex: "bin/ls", "bin/cat"...
 * */
char	*path_join(const char *path, const char *cmd)
{
	char *path_slash;
	char *full_path;

	path_slash = ft_strjoin(path, "/");
	if (!path_slash)
		return (NULL);
	full_path = ft_strjoin(path_slash, cmd);
	if (!full_path)
	{
		free(path_slash);
		return (NULL);
	}
	free(path_slash);
	return (full_path);
}
