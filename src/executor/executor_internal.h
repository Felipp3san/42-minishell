/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:47:54 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 11:25:14 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include "minishell.h"

# define CMD_NOT_FOUND 127

typedef struct s_exec
{
	t_command	*cmd;
	int			pipe_fd[2];
	int			input_fd;
	int			output_fd;
	t_bool		last;
}	t_exec;

// executor_utils.c
void	init_exec(t_exec *exec, t_shell *shell);
t_bool	is_builtin(char *cmd);
t_bool	is_single_cmd(t_command *commands);

// executor_heredoc.c
int		heredoc(char *delimiter);

// executor_external.c
void	execute_external(t_exec *exec, t_shell *shell);

// execute_builtin.c
int		execute_builtin(t_exec *exec, t_shell *shell);
int		execute_single_builtin(t_exec *exec, t_shell *shell);

// executor_pipeline.c
int		pipeline(t_exec *exec, t_shell *shell);

// executor_redirection.c
int		apply_redirections(t_exec *exec);

#endif
