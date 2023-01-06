/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:37:29 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/06 11:12:42 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_in_str(char *sep, char c)
{
	int	i;

	i = 0;
	while (sep[i])
		if (sep[i++] == c)
			return (true);
	return (false);
}

static int	tab_len(char *str, char *sep)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (str[i])
	{
		if (!is_in_str(sep, str[i]))
			if ((!is_in_str(sep, str[i + 1]))
				|| !str[i + 1])
				n++;
		if (str[i] == '"')
			i += find_quote(str + i + 1, '"');
		else if (str[i] == '\'')
			i += find_quote(str + i + 1, '\'');
		i++;
	}
	return (n);
}

static char	**split_loop(char **tab, char const *s, char *sep)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (!s[i] || (is_in_str(sep, s[i])))
		{
			if (j < i)
			{
				tmp = ft_substr(s, j, i - j);
				if (!tmp)
				{
					free_tab(tab);
					return (NULL);
				}
				add_to_tab(tab, remove_quotes(tmp));
			}
			j = i + 1;
		}
		i += skip_if_quotes(s, i);
	}
	return (tab);
}

char	**ft_split_quotes(char const *s, char *sep)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = ft_calloc(tab_len((char *)s, sep) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (split_loop(tab, s, sep));
}
