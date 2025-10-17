/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:04:14 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 22:40:19 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

//builtins
int		builtin_exit(t_command *cmd, t_shell *shell);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_env **env);
int		builtin_pwd(void);
int		builtin_export(t_env **env, const char *variable);
int		builtin_env(t_env *env);
int		builtin_unset(t_env **env, char *variable);

// helpers
void	free_var(char *name, char *value);
int		split_assignment(const char *variable, char **out_name, char **out_value);
int		is_valid_name(char *name);
int		name_cmp(const char *a, const char *b);
int		sort_exp_list(t_env *head);
int		export_print_list(t_env **env);
t_env	*search_variable(t_env *env, char *name);
t_env	*copy_env_list(t_env *head);

#endif
