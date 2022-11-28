/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opnstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:44:47 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/27 22:03:03 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

char	*ft_opnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (i < len && big[i])
	{
		j = 0;
		while (i + j < len && big[i + j] == little[j])
		{
			if (!big[i + j])
				return (NULL);
			j++;
			if (!little[j]
				&& big[i + j] != little[j - 1]
				/* ERREUR DE READ lorsque i = 0 dans big */
				&& (big[i - 1] != little[j - 1]))
				return ((char *)&big[i]);
		}
		i++;
	}
	return (NULL);
}
