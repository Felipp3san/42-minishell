/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:56:06 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/11 17:45:23 by jfernand         ###   ########.fr       */
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
t_env	*env_new(char *content);
void	env_append(t_env **head, t_env *new_node);
void	env_prepend(t_env **head, t_env *new_node);

// ─────────────────────────────────────────────
// Conversion
// ─────────────────────────────────────────────
t_env	*env_arr_to_lst(char **envp);
char	**env_list_to_arr(t_env *envp);
char	*env_get_arr(char **envp, const char *var);
char	*env_get_lst(t_env *envp, const char *var);
// ─────────────────────────────────────────────
// Search & Deletion
// ─────────────────────────────────────────────
t_env	*env_find(t_env *head, const char *prefix);
int		env_size(t_env *head);
int		env_delete(t_env **head, const char *name);

// ─────────────────────────────────────────────
// Cleanup & Debug
// ─────────────────────────────────────────────
void	env_free_all(t_env **head);
void	env_print(t_env *head);
void	env_free(char **envp);

#endif

