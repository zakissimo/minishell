/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:16:51 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/19 09:35:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_if_quotes(const char *s, int i)
{
	if (s[i] == '"')
		return (find_quote(s + i + 1, '"') + 1);
	else if (s[i] == '\'')
		return (find_quote(s + i + 1, '\'') + 1);
	return (1);
}

int	ft_isprint_nospace_nodollar(int c)
{
	return ((c > ' ' && c <= '~') && c != '$');
}

int	ft_isprint_nospace(int c)
{
	return ((c > ' ' && c <= '~'));
}

void	free_tab(void *t)
{
	int		i;
	char	**tab;

	i = 0;
	tab = (char **)t;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	add_to_tab(char **tab, char *str)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	tab[i] = str;
}
