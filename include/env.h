/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:56:06 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/18 02:12:26 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stddef.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// env_lst.c
t_env	*env_lst_new(char *name, char *value);
void	env_lst_add_back(t_env **head, t_env *new_node);
void	env_lst_add_front(t_env **head, t_env *new_node);
void	env_lst_clear(t_env **head);
size_t	env_lst_size(t_env *env);

// env_get.c
char	*env_get_arr(char **envp, const char *var);
char	*env_get_lst(t_env *envp, const char *var);

// env_to.c
t_env	*env_arr_to_lst(char **envp);
char	**env_list_to_arr(t_env *envp);

// env_utils.c
int		env_var_delete(t_env **head, char *name);
void	env_arr_free(char **envp);
void	env_lst_print(t_env *head);

#endif
