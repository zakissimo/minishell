/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:05:48 by zhabri            #+#    #+#             */
/*   Updated: 2022/09/29 09:24:03 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest == src)
		return (dest);
	s = (unsigned char *)src;
	d = dest;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (0 < n)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	}
	return (dest);
}
