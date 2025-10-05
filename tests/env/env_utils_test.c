/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 17:01:22 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/04 18:50:22 by fde-alme         ###   ########.fr       */
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
	char	*std_val;
	char	*ft_val;

	(void)argc;
	(void)argv;
	list_clone = env_clone(envp);

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

	// Get env
	std_val = getenv("PATH");
	if (std_val)
		ft_printf("getenv (PATH): %s\n", std_val);

	ft_val = getenv("HOME");
	if (ft_val)
		ft_printf("getenv (HOME): %s\n", ft_val);

	ft_val = getenv("HOMES");
	if (ft_val)
		ft_printf("getenv (HOMES): %s\n", ft_val);

	ft_val = getenv("");
	if (ft_val)
		ft_printf("getenv (""): %s\n", ft_val);

	ft_val = env_get(list_clone, "PATH");
	if (ft_val)
		ft_printf("env_get (PATH): %s\n", ft_val);

	ft_val = env_get(list_clone, "HOME");
	if (ft_val)
		ft_printf("env_get (HOME): %s\n", ft_val);

	ft_val = env_get(list_clone, "HOMES");
	if (ft_val)
		ft_printf("env_get (HOMES): %s\n", ft_val);

	ft_val = env_get(list_clone, "");
	if (ft_val)
		ft_printf("env_get (""): %s\n", ft_val);

	ft_val = env_get(list_clone, NULL);
	if (ft_val)
		ft_printf("env_get (NULL) %s\n", ft_val);

	ft_lstclear(&list_clone, free);
	return (0);
}
