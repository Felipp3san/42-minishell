/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_helpers.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:40:56 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/17 12:50:17 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_HELPERS_H
# define INTERNAL_HELPERS_H

# include "env.h"

int		is_valid_name(char *name);
int		name_cmp(const char *a, const char *b);
int		sort_exp_list(t_env *head);
int		export_print_list(t_env **env);
t_env	*search_variable(t_env *env, char *name);
t_env	*copy_env_list(t_env *head);

#endif
