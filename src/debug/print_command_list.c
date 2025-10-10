/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:02:53 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 15:38:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "types.h"

static char	*get_type(t_token_type type)
{
	if (type == OUTPUT)
		return ("OUTPUT");
	else if (type == INPUT)
		return ("INPUT");
	else if (type == HEREDOC)
		return ("HEREDOC");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == WORD)
		return ("WORD");
	else
		return (NULL);
}

void	print_redir_list(t_redir *redir)
{
	size_t	i;

	i = 1;
	while (redir)
	{
		ft_printf(MAGENTA"\tRedir %d\n"RESET, i);
		ft_printf("\tAddress: %p\n", redir);
		ft_printf("\tValue: %s\n", redir->value);
		ft_printf("\tType: %s\n", get_type(redir->type));
		ft_printf("\tPrevious: %p\n", redir->previous);
		ft_printf("\n");
		redir = redir->next;
		i++;
	}
}

void	print_command_list(t_command *command)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (command)
	{
		ft_printf(CYAN"COMMAND %d\n"RESET, i);
		ft_printf("Address: %p\n", command);
		ft_printf("argv: [");
		j = 0;
		while (command->argv[j])
		{
			ft_printf("%s", command->argv[j]);
			if (command->argv[j + 1] != NULL)
				ft_printf(", ");
			j++;
		}
		ft_printf("]\n");
		ft_printf("Size: %d\n", command->size);
		ft_printf("Capacity: %d\n", command->capacity);
		print_redir_list(command->redirs);
		ft_printf("Next: %p\n", command->next);
		ft_printf("Previous: %p\n", command->previous);
		ft_printf("\n");
		command = command->next;
		i++;
	}
}
