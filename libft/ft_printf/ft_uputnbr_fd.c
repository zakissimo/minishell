/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:49:17 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/15 18:46:53 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(size_t i, int fd, int *len)
{
	char	d;

	if (i > 9)
		rec(i / 10, fd, len);
	d = i % 10 + '0';
	(*len)++;
	write(fd, &d, 1);
}

int	ft_uputnbr_fd(size_t n, int fd)
{
	int		len;

	len = 0;
	rec(n, fd, &len);
	return (len);
}
