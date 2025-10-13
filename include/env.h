/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:56:06 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/13 19:52:35 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// ─────────────────────────────────────────────
// Creation & Insertion
// ─────────────────────────────────────────────
t_env	*env_lst_new(char *content);
void	env_lst_add_back(t_env **head, t_env *new_node);
void	env_lst_add_front(t_env **head, t_env *new_node);

// ─────────────────────────────────────────────
// Conversion
// ─────────────────────────────────────────────
t_env	*env_arr_to_lst(char **envp);
char	**env_list_to_arr(t_env *envp);
char	*env_get_arr(char **envp, const char *var);
char	*env_get_lst(t_env *envp, const char *var);
t_env	*copy_env_list(t_env *head);
// ─────────────────────────────────────────────
// Search & Deletion
// ─────────────────────────────────────────────
int		env_lst_size(t_env *head);
int		env_var_delete(t_env **head, const char *name);

// ─────────────────────────────────────────────
// Cleanup & Debug
// ─────────────────────────────────────────────
void	env_lst_clear(t_env **head);
void	env_lst_print(t_env *head);
void	env_free(char **envp);

#endif

