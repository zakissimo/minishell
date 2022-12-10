/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:58:39 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/10 20:22:32 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"
#include <stdlib.h>

int	get_longest_str(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	return (ft_strlen(s2));
}

int	ft_isprint_nospace_nodollar(int c)
{
	return ((c > ' ' && c <= '~') && c != '$');
}

int	ft_isprint_nospace(int c)
{
	return ((c > ' ' && c <= '~'));
}

t_list	**str_tab_to_list(char **tab)
{
	int		i;
	t_list	**head;

	i = 0;
	head = malloc(sizeof(t_list *));
	*head = NULL;
	while (tab[i])
		ft_lstadd_back(head, ft_lstnew(ft_strdup(tab[i++])));
	return (head);
}
