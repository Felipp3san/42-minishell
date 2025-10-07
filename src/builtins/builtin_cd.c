/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:12:38 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/04 18:28:54 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "types.h"
#include "utils.h"
#include <string.h>

int	builtin_cd(char **path)
{
	char *target;

	if (!path || !*path)
	{
		//temporary till we get ours working
		target = getenv("HOME");
		if (!target)
			return (ERROR);
		chdir(target);
	}
	else
		target = *path;
	if (chdir(target) != 0)
	{
		print_error("cd",target, strerror(errno));
    	return (ERROR);
	}
	return (SUCCESS);
}
