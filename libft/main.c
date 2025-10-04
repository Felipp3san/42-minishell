/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:16:57 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/03 18:18:55 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

void test_case(const char *str, int base)
{
	char *end_std, *end_ft;
	errno = 0;
	long std_val = strtoll(str, &end_std, base);
	int std_errno = errno;

	errno = 0;
	long ft_val = ft_strtoll(str, &end_ft, base);
	int ft_errno = errno;

	printf("Input: \"%s\" (base %d)\n", str, base);
	printf("  strtoll:   %ld (end=\"%s\", errno=%d)\n",
			std_val, *end_std ? end_std : "END", std_errno);
	printf("  ft_strtoll:%ld (end=\"%s\", errno=%d)\n",
			ft_val, *end_ft ? end_ft : "END", ft_errno);
	printf("------------------------------------------------\n");
}

int main(void)
{
	// Basic cases
	test_case("42", 10);
	test_case("   123", 10);
	test_case("+77", 10);
	test_case("-99", 10);

	// Different bases
	test_case("0xFF", 0);
	test_case("075", 0);
	test_case("1011", 2);
	test_case("deadBEEF", 16);
	test_case("zzz", 36);

	// Overflow / underflow
	char buf[64];
	sprintf(buf, "%lld", (long long)LLONG_MAX);
	test_case(buf, 10);

	sprintf(buf, "%lld", (long long)LLONG_MIN);
	test_case(buf, 10);

	// Out of range
	test_case("99999999999999999999999999999999999", 10);
	test_case("-99999999999999999999999999999999999", 10);

	// Invalid base
	test_case("843821", 40);
	test_case("843821", 40);

	// Invalid base
	test_case("843821", -1);
	test_case("843821", -1);

	// Invalid input
	test_case("abc", 10);
	test_case("", 10);
	test_case("   +", 10);

	return 0;
}
