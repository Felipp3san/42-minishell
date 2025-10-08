/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:47:54 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/08 15:51:22 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_INTERNAL_H
# define EXECUTOR_INTERNAL_H

# include "minishell.h"
# include "types.h"
# include "command.h"
# include <fcntl.h>

typedef struct	s_exec
{
	t_command	*cmd;
	int			pipe_fd[2];
	int			input_fd;
	int			output_fd;
	char		**envp;
	t_bool		last;
}	t_exec;

// executor_utils.c
void	init_exec(t_exec *exec);
t_bool	is_builtin(t_command *command);
t_bool	is_single_command(t_list *commands);

// executor_heredoc.c
int		heredoc(char *delimiter);

// executor_external.c
int		fork_child(t_exec *exec);
int		execute_external(t_exec *exec);

// execute_builtin.c
int		execute_builtin(t_exec *exec, t_shell *shell);

// executor_pipeline.c
int		pipeline(t_exec *exec, t_shell *shell);

// executor_redirection.c
int		setup_redirs(t_exec *exec);

#endif
