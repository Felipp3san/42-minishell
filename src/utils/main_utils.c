/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfernand <jfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:34:36 by jfernand          #+#    #+#             */
/*   Updated: 2025/10/16 18:57:17 by jfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"
#include "../parser/parser_internal.h"
#include "signals.h"
#include "tokenizer.h"
#include "parser.h"
#include "ui.h"
#include "types.h"
#include "env.h"
#include "expander.h"
#include "executor.h"
#include "debug.h"
#include "builtins.h"

void    full_clean(t_shell *shell)
{
    if (shell->current_dir)
	{
		free(shell->current_dir);
		shell->current_dir = NULL;
	}
	if (shell->env_lst)
		env_lst_clear(&shell->env_lst);
	rl_clear_history();
}
int    get_commands(t_shell *shell)
{
    shell->tokens = tokenize(shell->user_input);
	if (!shell->tokens)
	{
		g_last_exit_code = 1;
		free_shell(shell, FALSE);
		return (ERROR);
	}
	shell->commands = parse(shell->tokens);
	if (!shell->commands)
	{
		g_last_exit_code = 1;
		free_shell(shell, FALSE);
		return (ERROR);
	}
    return (SUCCESS);
}