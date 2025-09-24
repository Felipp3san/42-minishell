/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:31:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/24 15:39:56 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stddef.h>

typedef struct s_shell
{
	char	**tokens;
	size_t	token_count;
	char	*current_dir;
	int		last_exit_status;
}	t_shell;

typedef enum e_state
{
	NORMAL,
	SINGLE,
	DOUBLE
}	t_state;

typedef struct s_tokenizer
{
	char	*buffer;
	char	*token;
	size_t	buf_len;
	t_state	state;
}	t_tokenizer;

typedef enum e_status
{
	SUCCESS = 0,
	ERROR = -1,
	ERR_SIGACTION = -2,
	ERR_MALLOC = -3
}	t_status;

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

# define RESET "\033[0m"
# define BOLD "\033[1m"
# define BLACK "\033[1;30m"
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define WHITE "\033[1;37m"

// ui.c
void	print_banner();

// handlers.c
void	sigint_handler(int sig);

// tokens.c
void	free_tokens(t_shell *shell);
int		tokens_append(t_shell *shell, char *str);
int		tokens_init(t_shell *shell);
void	tokens_print(char **tokens);

// tokenizer.c
int		tokenizer(char const *str, t_shell *shell);

// buffer.c
void	buffer_reset(t_tokenizer *tok);
int		buffer_init(t_tokenizer *tok);
int		buffer_flush(t_tokenizer *tok, char **out);
int		buffer_append(t_tokenizer *tok, char ch);

// utils.c
void	free_exit(t_shell *shell);

#endif
