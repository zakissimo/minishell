/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:09:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/19 13:44:16 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoinf(char *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	len = 0;
	if (s1 && s2)
		len = ft_strlen(s1) + ft_strlen(s2);
	else if (s1)
		len = ft_strlen(s1);
	else if (s2)
		len = ft_strlen(s2);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (str);
	i = -1;
	while (s1 && i++ < len && s1[i])
		str[i] = s1[i];
	j = 0;
	while (s2 && i < len && s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
