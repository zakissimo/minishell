/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 21:28:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/29 11:16:33 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	rec(char *out, long n, int idx)
{
	if (n < 0)
	{
		n *= -1;
		out[idx++] = '-';
	}
	if (n > 9)
		idx = rec(out, n / 10, idx);
	out[idx] = (n % 10) + '0';
	return (++idx);
}

static int	nbr_len(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 1;
	else if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*out;

	out = malloc((nbr_len(n) + 1) * sizeof(char));
	if (!out)
		return (out);
	rec(out, n, 0);
	out[nbr_len(n)] = '\0';
	return (out);
}
