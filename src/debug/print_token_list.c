/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:08:19 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 11:19:07 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

char	*get_type(t_token_type type)
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

void	print_token_list(t_token *token)
{
	size_t	i;
	
	i = 1;
	while (token)
	{
		ft_printf("TOKEN %d\n", i);
		ft_printf("Address: %p\n", token);
		ft_printf("Value: %s\n", token->value);
		ft_printf("type: %s\n", get_type(token->type));
		ft_printf("Next: %p\n", token->next);
		ft_printf("Previous: %p\n", token->previous);
		ft_printf("\n\n");
		token = token->next;
		i++;
	}
}
