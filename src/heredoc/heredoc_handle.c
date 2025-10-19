/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 10:48:01 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/19 12:10:08 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc_internal.h"
#include "minishell.h"
#include "token.h"

int	heredoc_handle(t_shell *shell)
{
	t_command *command;
	t_redir	*redir;

	command = shell->commands;
	while (command)
	{
		redir = command->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->heredoc_fd = heredoc_read(shell, redir->value);
				if (redir->heredoc_fd == -1)
					return (ERROR);
			}
			redir = redir->next;
		}
		command = command->next;
	}
	return (SUCCESS);
}
