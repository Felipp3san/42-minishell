/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:17:17 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/01 18:49:52 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"

void	free_redir(void *content)
{
	t_redir	*redir;

	redir = (t_redir *) content;
	if (!redir)
		return ;
	if (redir->filename)
		free(redir->filename);
	free(redir);
}

void	free_command(void *content)
{
	t_command	*command;

	if (!content)
		return ;
	command = (t_command *) content;
	if (command->argv)
		free_argv(command);
	if (command->redirs)
		ft_lstclear(&command->redirs, free_redir);
	free(command);
}

void	free_argv(t_command	*command)
{
	size_t	i;

	i = 0;
	while (command->argv[i] != NULL)
	{
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
	command->argv = NULL;
}
