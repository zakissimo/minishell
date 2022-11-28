/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:15:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/09/29 08:35:27 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*arr;

	i = 0;
	arr = (char *)s;
	while (i < n && arr[i] != (char)c)
		i++;
	if (i < n && arr[i] == (char)c)
		return (&arr[i]);
	return (0);
}
