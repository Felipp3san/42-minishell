/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 11:48:13 by fde-alme          #+#    #+#             */
/*   Updated: 2025/09/23 12:22:09 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <unistd.h>

void	sigint_handler(int sig)
{
	(void) sig;

	//ft_printf("Parent SIGINT captured\n");
	write(STDOUT_FILENO, "\n", 1);

	// Tell readline we’re on a new line and refresh the prompt
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
