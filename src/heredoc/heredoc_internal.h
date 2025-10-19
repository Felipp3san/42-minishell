/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:08:00 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 13:04:48 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_INTERNAL_H
# define HEREDOC_INTERNAL_H

# include "minishell.h"

int		heredoc_read(t_shell *shell, char *delimiter);

// heredoc_utils.h
void	print_err_heredoc(const char *delimiter);

#endif
