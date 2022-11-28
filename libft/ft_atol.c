/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:25:53 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/18 11:43:26 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static long long	check_neg(int neg, long long nb)
{
	if (neg)
		nb *= -1;
	return (nb);
}

static int	check_overflow(size_t nb, int neg)
{
	if (nb > LONG_MAX && !neg)
		return (-1);
	if (nb > (size_t)LONG_MAX + 1 && neg)
		return (0);
	return (1);
}

long	ft_atol(const char *nptr)
{
	int			i;
	size_t		nb;
	int			neg;

	i = 0;
	nb = 0;
	neg = 0;
	while (ft_is_space(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg++;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		nb *= 10;
		nb += nptr[i] - '0';
		if (check_overflow(nb, neg) != 1)
			return (check_overflow(nb, neg));
		i++;
	}
	return ((long)check_neg(neg, nb));
}
