/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:04:14 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/16 18:28:10 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

int		builtin_exit(char **args, t_shell *shell);
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_env **env);
int		builtin_pwd(void);
int		builtin_export(t_env **env, const char *variable);
int		builtin_env(t_env *env);
int		builtin_unset(t_env **env, char *variable);
void	free_var(char *name, char *value);
int		split_assignment(const char *variable, char **out_name, char **out_value);

#endif
