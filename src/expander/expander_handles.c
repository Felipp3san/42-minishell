/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:59:56 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/17 20:01:12 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_internal.h"
#include "minishell.h"
#include "libft.h"
#include "types.h"

char	*handle_dollar(t_shell *shell, const char *str, size_t *i, int dquotes)
{
	size_t	start;
	char	*var;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->last_exit_code));
	}
	else if (!dquotes && (str[*i] == '"' || str[*i] == '\''))
		return (NULL);
	if (!is_valid_var_char(str[*i]))
		return (ft_strdup("$"));
	else
	{
		start = *i;
		while (is_valid_var_char(str[*i]))
			(*i)++;
		var = ft_substr(str, start, *i - start);
		value = env_get_lst(shell->env_lst, var);
		if (!value)
			return (free(var), NULL);
		return (free(var), ft_strdup(value));
	}
}

char	*handle_normal(const char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '\"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_squote(const char *str, size_t *i)
{
	size_t	start;

	(*i)++;
	start = *i;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start - 1));
}

static char	*handle_dquote_str(const char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '\"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*handle_dquote(t_shell *shell, const char *str, size_t *i)
{
	char	*ret;

	ret = ft_strdup("");
	(*i)++;
	while (str[*i] != '\"')
	{
		if (str[*i] == '$')
			ret = ft_strjoin_free(ret, handle_dollar(shell, str, i, TRUE));
		else
			ret = ft_strjoin_free(ret, handle_dquote_str(str, i));
	}
	(*i)++;
	return (ret);
}
