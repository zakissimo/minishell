/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 14:58:39 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/13 13:17:27 by zhabri           ###   ########.fr       */
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

int	count_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '"')
			i += find_quote(str + i + 1, '"');
		if (str[i] == '\'')
			i += find_quote(str + i + 1, '\'');
		if (str[i] == '"' || str[i] == '\'')
			count += 2;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*ret;
	int		double_q;
	int		single_q;

	ret = ft_calloc(((ft_strlen(str) - count_quotes(str) + 1)), sizeof(char));
	double_q = 0;
	single_q = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && !single_q)
			double_q = !double_q;
		else if (str[i] == '\'' && !double_q)
			single_q = !single_q;
		else if ((str[i] == '"' && single_q)
			|| (str[i] == '\'' && double_q)
			|| (str[i] != '"' && str[i] != '\''))
			ret[j++] = str[i];
		i++;
	}
	free(str);
	return (ret);
}
