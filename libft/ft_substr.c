/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 08:25:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/09/29 12:11:55 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	to_malloc;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		to_malloc = 0;
	else if (ft_strlen(s) - start < len)
		to_malloc = ft_strlen(s) - start;
	else
		to_malloc = len;
	str = malloc((to_malloc + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < to_malloc && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
