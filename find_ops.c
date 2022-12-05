/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/05 13:20:40 by zhabri           ###   ########.fr       */
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

t_token	*init_token(const char *str, int str_idx, int idx, t_label label)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->idx = idx;
	new->str_idx = str_idx;
	new->label = label;
	new->str = str;
	return (new);
}

t_label	get_label(const char *op)
{
	int					i;
	static const char	*op_tab[6] = {"<<", ">>", "|", ">", "<", NULL};

	i = 0;
	while (ft_strncmp(op_tab[i], op, 2))
		i++;
	if (i < 4)
		return (i);
	return (4);
}

int	add_ops(const char *input, t_list **head, int i)
{
	int						j;
	int						n;
	static int				idx;
	t_token					*op;
	static const char		*op_tab[6] = {"<<", ">>", "|", ">", "<", NULL};

	j = 0;
	n = i;
	if (!i)
		idx = i;
	while (op_tab[j])
	{
		if (!ft_strncmp(input + i, op_tab[j], ft_strlen(op_tab[j])))
		{
			op = init_token(ft_strdup(op_tab[j]), i, idx, get_label(op_tab[j]));
			i += ft_strlen(op_tab[j]);
			ft_lstadd_back(head, ft_lstnew(op));
			idx++;
		}
		j++;
	}
	return (i - n);
}

void	get_ops(const char *input, t_list **head)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		i += add_ops(input, head, i);
		if (input[i] == '"' || input[i] == '\'')
			i += find_quote(input + i + 1, input[i]);
		i++;
	}
}
