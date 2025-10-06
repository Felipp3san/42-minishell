/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:19:18 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:24:00 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "path.h"

int	main(void)
{
	const char	*paths[] = {
			"/bin",
			"/usr/bin/",
			"/sbin",
			"",
			".",
			"./bin",
			"../usr/bin",
			"/usr//bin",
			"/usr//",
			"//bin",
			NULL
		};
	const char	*cmds[] = {
		"ls",
		"grep",
		"ifconfig",
		"",
		"cat",
		"env",
		NULL
	};
	char	*joined;
	int		i;
	int		j;

	i = 0;
	while (paths[i])
	{
		j = 0;
		while (cmds[j])
		{
			joined = path_join(paths[i], cmds[j]);
			if (joined == NULL)
			{
				ft_printf("❌ path_join(\"%s\", \"%s\") -> NULL (allocation failed)\n",
					paths[i], cmds[j]);
				continue;
			}
			ft_printf("✅ path: %s | cmd: %s -> %s\n", paths[i], cmds[j], joined);
			free(joined);
			j++;
		}
		i++;
	}
	return (0);
}
