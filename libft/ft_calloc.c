/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:19:53 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/05 21:56:05 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	n;
	void	*arr;

	if (!nmemb || !size)
	{
		nmemb = 1;
		size = 1;
	}
	n = nmemb * size;
	if (n / nmemb != size)
		return (NULL);
	arr = malloc(n);
	if (!arr || !n)
		return (arr);
	ft_bzero(arr, n);
	return (arr);
}
