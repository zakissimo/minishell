/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:09:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/08 15:39:28 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinf(char *s1, char const *s2)
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
	free(s1);
	return (str);
}
