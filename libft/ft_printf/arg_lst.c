/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:50:24 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/16 09:05:16 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_flags(char c)
{
	int			i;
	const char	*flags;

	i = 0;
	flags = "cspdiuxX%b";
	while (flags[i])
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}

t_list	*arg_lst(const char *str, t_list *head)
{
	int			i;
	t_list		*n;
	t_node		*node;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && char_in_flags(str[i + 1]))
		{
			node = malloc(sizeof(t_node));
			if (!node)
				return (ft_lstclear(&head, free), NULL);
			node->i = i;
			node->flag = str[i + 1];
			n = ft_lstnew(node);
			if (!n)
				return (ft_lstclear(&head, free), NULL);
			ft_lstadd_back(&head, n);
			if (str[i + 1] == '%')
				i++;
		}
		i++;
	}
	return (head);
}
