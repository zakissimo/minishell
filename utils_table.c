/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 11:22:00 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/10 13:04:27 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tab_dup(char **tab, int tab_len)
{
	int		i;
	char	**t;

	t = ft_calloc(tab_len + 1, sizeof(char *));
	i = 0;
	while (i < tab_len)
	{
		t[i] = ft_strdup(tab[i]);
		i++;
	}
	return (t);
}

void	free_tab_bis(void *t)
{
	int		i;
	char	**tab;

	i = 1;
	tab = (char **)t;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
