/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 10:25:53 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/05 22:05:32 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	check_neg(int neg, int nb)
{
	if (neg)
		nb *= -1;
	return (nb);
}

static int	check_overflow(long long nb, int neg)
{
	if (nb > INT_MAX && !neg)
		return (-1);
	if (nb > (long)INT_MAX + 1 && neg)
		return (0);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	long long	nb;
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
	return ((int)check_neg(neg, nb));
}
