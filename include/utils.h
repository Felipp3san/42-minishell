/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:30:02 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 10:42:19 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	free_split(char **arr);
void	exit_shell(t_shell *shell, int err_code);

// print_error.c
void	print_error(const char *cmd_name, const char *msg, char *optional);
int		print_error_return(const char *cmd_name, const char *msg, int code);
int		print_exit(t_shell *shell, char *cmd_name, char *msg, int code);

// ft_is.c
int		is_separator(char ch);
int		is_space(char ch);
int		is_single_quote(char ch);
int		is_double_quote(char ch);

#endif
