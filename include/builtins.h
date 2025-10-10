/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:04:14 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/10 08:12:56 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	builtin_exit(char **argv);
int	builtin_exit(char **path);
int	builtin_echo(char **args);
int builtin_cd(void);

#endif
