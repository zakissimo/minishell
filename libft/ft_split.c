/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:37:29 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/13 19:59:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	tab_len(char *str, char sep)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] != sep)
			if ((str[i + 1] == sep)
				|| !str[i + 1])
				n++;
		i++;
	}
	return (n);
}

static void	add_to_tab(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	tab[i] = str;
}

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**split_loop(char **tab, char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (!s[i] || (s[i] == c))
		{
			if (j < i)
			{
				tmp = ft_substr(s, j, i - j);
				if (!tmp)
				{
					free_tab(tab);
					return (NULL);
				}
				add_to_tab(tab, tmp);
			}
			j = i + 1;
		}
		i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(tab_len((char *)s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (split_loop(tab, s, c));
}
