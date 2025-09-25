/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:31:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/25 18:37:01 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include "types.h"
# include "token.h"
# include "buffer.h"

# define PROMPT "\001\033[1;36m\002minishell>\001\033[0m\002 "

typedef struct s_shell
{
	char	*current_dir;
	int		last_exit_status;
}	t_shell;

// ui.c
void	print_banner();

// handlers.c
void	sigint_handler(int sig);

// tokenizer.c
int		tokenizer(char const *str, t_shell *shell);
void	add_token(t_token *tok, t_buffer *buffer);

// tokenizer_utils.c
t_bool	is_space(char ch);
t_bool	is_single_quote(char ch);
t_bool	is_double_quote(char ch);
t_bool	is_operator(char ch);

// tokenizer_modes.c
void	normal_mode(t_token *tok, char ch);
void	single_mode(t_token *tok, char ch);
void	double_mode(t_token *tok, char ch);
void	operator_mode(t_token *tok, char ch);

// utils.c
void	free_exit(t_shell *shell);

#endif
