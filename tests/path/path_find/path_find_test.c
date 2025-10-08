/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:17:23 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 19:05:55 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "path.h"
#include "libft.h"

/**
 * Example expected behavior:
 * path_find("ls", envp)       -> "/bin/ls"
 * path_find("grep", envp)     -> "/usr/bin/grep"
 * path_find("idontexist", envp) -> NULL
 */

int	main(int argc, char	**argv, char **envp)
{
	const char	*cmds[] = {
			"ls",
			"grep",
			"cat",
			"bash",
			"echo",
			"sh",
			"env",
			"pwd",
			"faillock",
			"idontexist123",
			NULL
		};
	char		*result;
	int			i;

	(void)argc;
	(void)argv;

	i = 0;
	while (cmds[i])
	{
		result = path_find(cmds[i], envp);
		if (result)
		{
			ft_printf("✅ %s -> %s\n", cmds[i], result);
			free(result);
		}
		else
			ft_printf("❌ %s -> not found\n", cmds[i]);
		i++;
	}
	return (0);
}
