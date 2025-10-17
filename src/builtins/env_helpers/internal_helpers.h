/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_helpers.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:40:56 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/16 17:28:26 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_HELPERS_H
# define INTERNAL_HELPERS_H

# include "libft.h"
# include "env.h"

int		is_valid_name(char *name);
int		name_cmp(const char *a, const char *b);
t_env	*search_variable(t_env *env, char *name);
int		sort_exp_list(t_env *head);
int		export_print_list(t_env **env);

#endif
