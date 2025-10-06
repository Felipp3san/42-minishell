/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_arr_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:19:27 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 19:20:32 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	main(int argc, char **argv, char **envp)
{
	char	*ft_val;

	(void) argc;
	(void) argv;
	ft_val = env_get_arr(envp, "PATH");
	if (ft_val)
		ft_printf("env_get (PATH): %s\n", ft_val);

	ft_val = env_get_arr(envp, "HOME");
	if (ft_val)
		ft_printf("env_get (HOME): %s\n", ft_val);

	ft_val = env_get_arr(envp, "HOMES");
	if (ft_val)
		ft_printf("env_get (HOMES): %s\n", ft_val);

	ft_val = env_get_arr(envp, "");
	if (ft_val)
		ft_printf("env_get (""): %s\n", ft_val);

	ft_val = env_get_arr(envp, NULL);
	if (ft_val)
		ft_printf("env_get (NULL) %s\n", ft_val);
}
