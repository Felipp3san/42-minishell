/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:31:58 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/23 18:05:26 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stddef.h>

typedef struct s_shell
{
	char **tokens;
	size_t	token_count;
	char *current_dir;
	int last_exit_status;
} t_shell;

typedef enum e_status
{
	SUCCESS = 0,
	ERROR = -1,
	ERR_SIGACTION = -2,
	ERR_MALLOC = -3
}	t_status;

typedef enum e_state
{
	NORMAL,
	SINGLE,
	DOUBLE
}	t_state;

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

// tokenizer.c
int	tokenizer(char const *str, t_shell *shell);
void	print_tokens(char **tokens);
void	free_tokens(t_shell *shell);

// buffer.c
int	buffer_append(char **buffer, size_t *buf_len, char ch);
int	buffer_flush(char **buffer, size_t *buf_len, t_shell *shell);
int	buffer_init(char **buffer);
void reset_buffer(char **buffer, size_t *buf_len);

#endif
