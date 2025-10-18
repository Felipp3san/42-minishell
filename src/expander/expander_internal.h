/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:01:14 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 20:01:53 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_INTERNAL_H
# define EXPANDER_INTERNAL_H

# include <stddef.h>
# include "minishell.h"

typedef struct s_quote_state
{
	int	single_opened;
	int	double_opened;
}	t_quote_state;

// expander.c
char	*expand_str(t_shell *shell, char *str);

// expander_utils.c
int		is_valid_var_char(char ch);

// expander_handle.c
char	*handle_squote(const char *str, size_t *i);
char	*handle_dquote(t_shell *shell, const char *str, size_t *i);
char	*handle_dollar(t_shell *shell, const char *str, size_t *i, int dquotes);
char	*handle_normal(const char *str, size_t *i);

// expander_heredoc.c
int		expand_heredoc(t_shell *shell, t_command *cmd);
int		handle_heredoc_exp(t_shell *shell, t_redir *redir);

#endif
