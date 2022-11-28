/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 08:20:11 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/02 23:27:58 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	long int	i;
	long int	src_len;
	size_t		dest_len;
	size_t		new_size;

	i = 0;
	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	dest_len = ft_strlen(dst);
	if (dest_len > size)
		dest_len = size;
	new_size = (size_t)(size - dest_len);
	while (new_size > 1 && src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
		new_size--;
	}
	if (i)
		dst[dest_len + i] = '\0';
	return (src_len + dest_len);
}
