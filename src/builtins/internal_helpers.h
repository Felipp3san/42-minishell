/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_helpers.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:40:56 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/10 16:02:22 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_HELPERS_H
# define INTERNAL_HELPERS_H

char	*build_new_var_string(const char *content, const char *value);
int		split_assignment(const char *variable, char **out_name, char **out_value);
int		is_valid_name(char *name);
int		name_cmp(const char *a, const char *b);
int		insert_in_list(t_list **env, t_list *new_node);
char	*build_new_var_string(const char *content, const char *value);
int		builtin_export(t_list **env, const char *variable);

#endif