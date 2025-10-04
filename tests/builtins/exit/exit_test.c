/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 17:20:15 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/03 17:38:11 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

int main(void)
{
	t_shell shell;
	int		err;

	char *args1[] = {"exit", NULL};
	char *args2[] = {"exit", "42", NULL};
	char *args3[] = {"exit", "abc", NULL};
	char *args4[] = {"exit", "1", "2", NULL};
	char *args5[] = {"exit", "9223372036854775807", NULL};
	char *args6[] = {"exit", "18446744073709551615", NULL};
	char *args7[] = {"exit", "0", NULL};
	char *args8[] = {"exit", "-1", NULL};
	char *args9[] = {"exit", "9223372036854775800", NULL};

	ft_memset(&shell, 0, sizeof(t_shell));
	
	ft_printf("\nTest 1: no arguments\n");
	err = builtin_exit(args1, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 2: numeric argument '42'\n");
	err = builtin_exit(args2, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 3: non-numeric argument 'abc'\n");
	err = builtin_exit(args3, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 4: too many arguments '1 2'\n");
	err = builtin_exit(args4, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 5: numeric argument long long limit '9223372036854775807'\n");
	err = builtin_exit(args5, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 6: non-numeric argument unsigned long long limit '18446744073709551615'\n");
	err = builtin_exit(args6, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 7: numeric argument '0'\n");
	err = builtin_exit(args7, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 8: numeric argument '-1'\n");
	err = builtin_exit(args8, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	ft_printf("\nTest 9: numeric argument '9223372036854775800'\n");
	err = builtin_exit(args9, &shell);
	if (err != ERROR)
		ft_printf("Exit code: %d, Exit function return: %d\n", shell.last_exit_status, err);

	return 0;
}
