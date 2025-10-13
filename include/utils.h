/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:30:02 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/12 12:27:49 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "minishell.h"

void	print_error(const char *cmd_name, const char *msg, const char *optional);
int		print_err_exit(const char *cmd_name, const char *msg, int exit_code);
void	free_split(char **arr);
void	exit_shell(t_shell *shell, int err_code);
char	*remove_quotes(char *str);

// ft_is.c
int	is_separator(char ch);
int	is_space(char ch);
int	is_single_quote(char ch);
int	is_double_quote(char ch);

#endif
