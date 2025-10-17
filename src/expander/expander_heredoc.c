/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:53:53 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 20:01:57 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"
#include "expander_internal.h"

int	expand_heredoc(t_shell *shell, t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == HEREDOC && redir->expand_heredoc)
		{
			if (redir->heredoc_fd != -1)
				if (handle_heredoc_exp(shell, redir) == ERROR)
					return (ERROR);
		}
		redir = redir->next;
	}
	return (SUCCESS);
}

int	handle_heredoc_exp(t_shell *shell, t_redir *redir)
{
	char	*line;
	char	*exp_line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) != 0)
		return (ERROR);
	line = get_next_line(redir->heredoc_fd);
	while (line)
	{
		exp_line = expand_str(shell, line);
		free(line);
		if (!exp_line)
		{
			line = get_next_line(redir->heredoc_fd);
			continue ;
		}
		write(pipe_fd[WRITE], exp_line, ft_strlen(exp_line));
		free(exp_line);
		line = get_next_line(redir->heredoc_fd);
	}
	close(pipe_fd[WRITE]);
	close(redir->heredoc_fd);
	redir->heredoc_fd = pipe_fd[READ];
	return (SUCCESS);
}
