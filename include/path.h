/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:26:28 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/06 18:41:57 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

char	*path_join(const char *path, const char *cmd);
char	*path_find(const char *cmd, char **envp);
char	**path_split(char *path);

#endif
