/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_lst_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:17:22 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 13:53:12 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*clone;
	char	*ft_val;

	(void) argc;
	(void) argv;
	clone = env_arr_to_lst(envp);
	ft_val = env_get_lst(clone, "PATH");
	if (ft_val)
		ft_printf("env_get (PATH): %s\n", ft_val);

	ft_val = env_get_lst(clone, "HOME");
	if (ft_val)
		ft_printf("env_get (HOME): %s\n", ft_val);

	ft_val = env_get_lst(clone, "HOMES");
	if (ft_val)
		ft_printf("env_get (HOMES): %s\n", ft_val);

	ft_val = env_get_lst(clone, "");
	if (ft_val)
		ft_printf("env_get (""): %s\n", ft_val);

	ft_val = env_get_lst(clone, NULL);
	if (ft_val)
		ft_printf("env_get (NULL) %s\n", ft_val);
}
