/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:23:35 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 15:03:14 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

t_command	*command_init(size_t size, t_type type)
{
	t_command	*command;
	char		**comm_arr;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	comm_arr = (char **) malloc(sizeof(char *) * (size + 1));
	if (!comm_arr)
	{
		free(command);
		return (NULL);
	}
	comm_arr[size] = NULL;
	command->type = type;
	return (command);
}

void	command_free(void *command)
{
	if (!command)
		return ;
	if (((t_command *)command)->comm_arr)
		free(((t_command *)command)->comm_arr);
	free(command);
}
