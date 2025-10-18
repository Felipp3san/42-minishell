/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:15:56 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 12:38:17 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stddef.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*previous;
}	t_token;

// token_lst.c
t_token	*token_lst_new(char *value, t_token_type type);
t_token	*token_lst_last(t_token *token);
void	token_lst_add_back(t_token **token_list, t_token *new_token);
void	token_lst_clear(t_token **token);
size_t	token_lst_size(t_token *token);

#endif
