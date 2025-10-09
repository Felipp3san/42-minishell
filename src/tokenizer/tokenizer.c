/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:37:46 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/09 12:44:25 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer_internal.h"
#include "libft.h"
#include "utils.h"

t_token	*append_operator(char **line, t_token **token_list, t_token_type type)
{
	t_token		*new_token;
	char		*value;
	int			offset;

	if (type == APPEND || type == HEREDOC)
		offset = 2;
	else
		offset = 1;
	value = ft_substr(*line, 0, offset);
	if (!value)
		return (NULL);
	new_token = token_lst_new(value, type);
	if (!new_token)
	{
		free(value);
		return (NULL);
	}
	token_lst_add_back(token_list, new_token);
	*line = *line + offset;
	return (new_token);
}

t_token	*handle_separator(char **line, t_token **token_list)
{
	if (!ft_strncmp(*line, "<<", 2))
		return (append_operator(line, token_list, HEREDOC));
	else if (!ft_strncmp(*line, ">>", 2))
		return (append_operator(line, token_list, APPEND));
	else if (!ft_strncmp(*line, "|", 1))
		return (append_operator(line, token_list, PIPE));
	else if (!ft_strncmp(*line, "<", 1))
		return (append_operator(line, token_list, INPUT));
	else if (!ft_strncmp(*line, ">", 1))
		return (append_operator(line, token_list, OUTPUT));
	return (NULL);
}

t_token	*append_word(char **line, t_token **token_list)
{
	const char	*start;
	t_token		*new_token;
	char		*word;

	new_token = NULL;
	start = *line;
	while (**line && !is_separator(**line) && !ft_isspace(**line))
	{
		if (is_single_quote(**line) || is_double_quote(**line))
			advance_to_next_quote(line);
		(*line)++;
	}
	word = ft_substr(start, 0, (*line) - start);
	if (!word)
		return (NULL);
	new_token = token_lst_new(word, WORD);
	if (!new_token)
	{
		free(word);
		return (NULL);
	}
	token_lst_add_back(token_list, new_token);
	return (new_token);
}

t_token	*tokenize(char *line)
{
	t_token	*token_list;

	token_list = NULL;
	if (has_open_quotes(line))
	{
		print_error("tokenizer", "input has open quotes", NULL);
		return (NULL);
	}
	while (*line)
	{
		skip_spaces(&line);
		if (is_separator(*line))
		{
			if (!handle_separator(&line, &token_list))
				return (token_lst_clear(&token_list), NULL);
		}
		else
		{
			if (!append_word(&line, &token_list))
				return (token_lst_clear(&token_list), NULL);
		}
	}
	return (token_list);
}
