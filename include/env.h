/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:56:06 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/04 18:47:29 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "libft.h"

void	env_free(char **envp);
t_list	*env_clone(char **envp);
char	**env_list_to_arr(t_list *envp);
char	*env_get(t_list *envp, const char *var);

#endif

