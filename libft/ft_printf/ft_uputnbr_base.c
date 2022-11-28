/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:11:40 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/15 18:47:02 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_errors(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strlen(str) <= 1)
		return (1);
	while (str[i])
	{
		if (str[i] == '+' || str[i] == '-')
			return (1);
		while (str[j])
		{
			if (i != j)
				if (str[i] == str[j])
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static void	print_nbr(size_t nb, const char *base, size_t size, int *len)
{
	char	d;

	if (nb > size - 1)
		print_nbr(nb / size, base, size, len);
	d = base[nb % size];
	write(1, &d, 1);
	(*len)++;
}

int	ft_uputnbr_base(size_t nb, const char *base)
{
	int	len;

	len = 0;
	if (check_errors(base))
		return (len);
	print_nbr(nb, base, ft_strlen(base), &len);
	return (len);
}
