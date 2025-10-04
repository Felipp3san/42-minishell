/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alme <fde-alme@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:13:49 by fde-alme          #+#    #+#             */
/*   Updated: 2025/10/04 15:38:38 by fde-alme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	check_prefix(const char *ptr, int *base);
int	from_base(int base, char ch);

static size_t	skip_spaces_and_sign(const char *nptr, int *sign)
{
	size_t	i;

	*sign = 1;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	check_overflow(long long nbr, int next_digit, int base, int sign)
{
	if (sign == -1)
	{
		if (-(nbr) > -(LLONG_MIN / base)
			|| (-(nbr) == -(LLONG_MIN / base)
				&& next_digit > (LLONG_MAX % base)))
		{
			errno = ERANGE;
			return (1);
		}
	}
	else
	{
		if (nbr > (LLONG_MAX / base)
			|| (nbr == (LLONG_MAX / base) && next_digit > (LLONG_MAX % base)))
		{
			errno = ERANGE;
			return (1);
		}
	}
	return (0);
}

long long	parse_digits(t_strtoll *stl, char *nptr, int base, char **endptr)
{
	long long	nbr;
	int			next_digit;
	const char	*digit_start;

	nbr = 0;
	digit_start = &nptr[stl->i];
	while (nptr[stl->i] != '\0' && from_base(base, nptr[stl->i]) != -1)
	{
		next_digit = from_base(base, nptr[stl->i]);
		if (check_overflow(nbr, next_digit, base, stl->sign))
		{
			if (stl->sign == -1)
				return (LLONG_MIN);
			else
				return (LLONG_MAX);
		}
		nbr = (nbr * base) + next_digit;
		stl->i++;
	}
	if (&nptr[stl->i] == digit_start)
		*endptr = (char *) nptr;
	else
		*endptr = (char *) &nptr[stl->i];
	return (nbr);
}

long long	ft_strtoll(const char *nptr, char **endptr, int base)
{
	t_strtoll	stl;

	stl.i = 0;
	if (base > 36 || base < 0)
	{
		errno = EINVAL;
		return (0);
	}
	stl.i = skip_spaces_and_sign(nptr, &stl.sign);
	if (base == 16 || base == 0)
		stl.i += check_prefix(&nptr[stl.i], &base);
	stl.nbr = parse_digits(&stl, (char *) nptr, base, endptr);
	return (stl.nbr * stl.sign);
}
