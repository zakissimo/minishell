/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:17:48 by zhabri            #+#    #+#             */
/*   Updated: 2022/09/29 17:56:35 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*str;
	int		str_len;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && is_in_set(s1[i], set))
		i++;
	str_len = ft_strlen(s1);
	while (str_len > i && is_in_set(s1[str_len - 1], set))
		str_len--;
	str_len -= i;
	str = malloc((str_len + 1) * sizeof(char));
	if (!str)
		return (str);
	j = 0;
	while (s1[i] && j < str_len)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
