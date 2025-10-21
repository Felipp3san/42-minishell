/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:25:16 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:46:40 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Split PATH var in an array of paths 
 * Ex: ["/usr/local/bin", "/usr/bin"...] */
char	**path_split(char *path)
{
	char	**paths;
	char	*skip_var;

	if (!path)
		return (NULL);
	skip_var = ft_strchr(path, '=');
	if (skip_var)
		path = skip_var + 1;
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}
