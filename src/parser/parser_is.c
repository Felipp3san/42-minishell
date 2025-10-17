/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 11:15:24 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 11:16:49 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	is_redir(t_token_type type)
{
	return (type == OUTPUT || type == INPUT || type == APPEND
		|| type == HEREDOC);
}

int	is_sep(t_token_type type)
{
	return (type == OUTPUT || type == INPUT || type == APPEND
		|| type == HEREDOC || type == PIPE);
}

int	is_word(t_token_type type)
{
	return (type == WORD);
}

int	is_heredoc(t_token_type type)
{
	return (type == HEREDOC);
}
