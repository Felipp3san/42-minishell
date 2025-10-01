/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:19:47 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/30 15:59:53 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "types.h"
#include "libft.h"

t_bool	is_pipe(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_redir(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return (TRUE);
	if (ft_strcmp(str, "<") == 0)
		return (TRUE);
	if (ft_strcmp(str, ">>") == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_operator2(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TRUE);
	if (ft_strcmp(str, ">") == 0)
		return (TRUE);
	if (ft_strcmp(str, ">>") == 0)
		return (TRUE);
	if (ft_strcmp(str, "<") == 0)
		return (TRUE);
	if (ft_strcmp(str, "<<") == 0)
		return (TRUE);
	return (FALSE);
}

void	get_operator(char *str, t_type *type)
{
	if (ft_strcmp(str, "|") == 0)
		*type = PIPE;
	if (ft_strcmp(str, ">") == 0)
		*type = OUTPUT;
	if (ft_strcmp(str, ">>") == 0)
		*type = APPEND;
	if (ft_strcmp(str, "<") == 0)
		*type = INPUT;
	if (ft_strcmp(str, "<<") == 0)
		*type = HEREDOC;
}

t_redir	*redir_create(char *filename, t_type type)
{
	t_redir	*redir;

	redir = (t_redir *) malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
		return (NULL);
	redir->type = type;
	return (redir);
}

t_command	*command_create(size_t	argv_size)
{
	t_command	*command;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->argv = (char **) malloc(sizeof(char **) * (argv_size + 1));
	if (!command->argv)
	{
		free(command);
		return (NULL);
	}
	command->redirs = NULL;
	return (command);
}

t_command	*add_as_cmd(t_list *start, size_t count, t_list **out)
{
	t_command	*command;
	t_list		*node;
	size_t		i;

	i = 0;
	if (count == 0)
		return (NULL);
	command = command_create(count);
	if (!command)
		return (NULL);
	while (i < count)
	{
		command->argv[i] = (char *) start->content;
		start = start->next;
		i++;
	}
	command->argv[i] = NULL;
	node = ft_lstnew(command);
	if (!node)
	{
		//TODO: free array
		free(command);
		return (NULL);
	}
	ft_lstadd_back(out, node);
	return (command);
}

t_redir	*add_as_redir(t_list *start, t_type type, t_list **out)
{
	t_redir	*redir;
	t_list	*node;

	redir = redir_create((char *) start->content, type);
	if (!redir)
		return (NULL);
	node = ft_lstnew(redir);
	if (!node)
	{
		free(redir->filename);
		free(redir);
		return (NULL);
	}
	ft_lstadd_back(out, node);
	return (redir);
}

void	move_forward(t_list **start, size_t count)
{
	while (count > 0)
	{
		(*start) = (*start)->next;
		count--;
	}
}

int	parser(t_list *tokens, t_list **out)
{
	t_command	*command;
	t_list		*node;
	t_list		*start;
	t_type		type;
	size_t		count;

	node = tokens;
	start = tokens;
	count = 0;
	type = UNSET;
	while (node)
	{
		if (is_operator2((char *)node->content))
		{
			if (type == PIPE || type == UNSET)
				command = add_as_cmd(start, count, out);
			else
				add_as_redir(start, type, &command->redirs);
			move_forward(&start, count + 1);
			count = 0;
			get_operator((char *)node->content, &type);
		}
		else
			count++;
		node = node->next;
	}
	if (type == PIPE || type == UNSET)
		add_as_cmd(start, count, out);
	else
		add_as_redir(start, type, &command->redirs);
	return (SUCCESS);
}
