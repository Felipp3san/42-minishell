/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:36:00 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:13:42 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "path.h"

static void	print_paths(char **arr)
{
	size_t	i;
	
	i = 0;
	while (arr[i])
	{
		ft_printf("%s\n", arr[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	char	**paths;
	size_t	i;

	(void)argc;
	(void)argv;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i];
		i++;
	}
	if (!path)
	{
		ft_printf("No path.\n", path);
		return (1);
	}
	ft_printf("%s\n\n", path);
	paths = path_split(path);
	if (!paths)
	{
		ft_printf("path_split error\n", path);
		return (1);
	}
	print_paths(paths);
	
	return (0);
}
