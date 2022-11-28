/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:09:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/09/30 23:04:44 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	if (!s1)
		return (NULL);
	if (s1 && s2)
		len = ft_strlen(s1) + ft_strlen(s2);
	else
		len = ft_strlen(s1);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (str);
	i = -1;
	while (++i < len && s1[i])
		str[i] = s1[i];
	j = 0;
	while (i < len && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
