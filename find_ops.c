/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/01 11:57:21 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_quote(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (i + 1);
	return (0);
}

void	find_ops(const char *input, t_list **head)
{
	int			i;
	int			j;
	t_token		*op;
	char		*op_tab[6];

	op_tab[0] = "||";
	op_tab[1] = "<";
	op_tab[2] = ">>";
	op_tab[3] = ">";
	op_tab[4] = "|";
	op_tab[5] = NULL;
	i = 0;
	while (input[i])
	{
		j = 0;
		while (op_tab[j])
		{
			if (!ft_strncmp(input + i, op_tab[j], ft_strlen(op_tab[j])))
			{
				op = malloc(sizeof(t_token));
				op->idx = i;
				op->str = op_tab[j];
				op->label = OP;
				ft_lstadd_back(head, ft_lstnew(op));
				i += ft_strlen(op_tab[j]);
			}
			j++;
		}
		if (input[i] == '"' || input[i] == '\'')
			i += find_quote(input + i + 1, input[i]);
		i++;
	}
}
