/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:34:16 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/02 23:28:47 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*arr1;
	unsigned char	*arr2;

	i = 0;
	arr1 = (unsigned char *)s1;
	arr2 = (unsigned char *)s2;
	if (!n)
		return (0);
	while (i < n - 1 && arr1[i] == arr2[i])
		i++;
	return ((int)(arr1[i] - arr2[i]));
}
