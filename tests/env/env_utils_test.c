/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:01:22 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 19:16:50 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"

int	env_compare(char **env1, char **env2)
{
	int	i;

	i = 0;
	while (env1[i] && env2[i])
	{
		if (ft_strcmp(env1[i], env2[i]) != 0)
			return (0); // mismatch
		i++;
	}
	return (env1[i] == NULL && env2[i] == NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_list	*list_clone;
	char	**arr_clone;

	(void)argc;
	(void)argv;
	list_clone = env_arr_to_list(envp);

	// Clone env as list
	if (!list_clone)
		ft_printf("env_clone failed\n");

	// Arr to list
	if (list_clone)
	{
		arr_clone = env_list_to_arr(list_clone);
		if (env_compare(arr_clone, envp))
			ft_printf("env_clone successfull!\n");
		else
			ft_printf("env_list_to_arr failed");
		env_free(arr_clone);
	}

	ft_lstclear(&list_clone, free);
	return (0);
}
