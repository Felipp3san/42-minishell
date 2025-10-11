/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_helpers.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:40:56 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/11 18:30:42 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_HELPERS_H
# define INTERNAL_HELPERS_H
# include "types.h"
# include "libft.h"
# include "env.h"

char	*build_new_var_string(const char *content, const char *value);
int		split_assignment(const char *variable, char **out_name, char **out_value);
int		is_valid_name(char *name);
int		name_cmp(const char *a, const char *b);
int		insert_in_list(t_env **env, t_env *new_node);
char	*build_new_var_string(const char *content, const char *value);
t_env	*search_variable(t_env *env, char *name);


#endif
