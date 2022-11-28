/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:49:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/05 22:17:03 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(long i, int fd, int *len)
{
	char	d;

	if (i < 0)
	{
		write(fd, "-", 1);
		(*len)++;
		i *= -1;
	}
	if (i > 9)
		rec(i / 10, fd, len);
	d = i % 10 + '0';
	(*len)++;
	write(fd, &d, 1);
}

int	ft_putnbr_fd(int n, int fd)
{
	long	i;
	int		len;

	len = 0;
	i = (long)n;
	rec(i, fd, &len);
	return (len);
}
