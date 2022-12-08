/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/08 15:26:26 by zhabri           ###   ########.fr       */
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
	new->arg = NULL;
	return (new);
}

t_label	get_label(const char *op)
{
	int					i;
	static const char	*op_tab[7] = {"<<", ">>", "|", ">", "<", "$", NULL};

	i = 0;
	while (ft_strncmp(op_tab[i], op, ft_strlen(op_tab[i])))
		i++;
	if (i < 5)
		return (i);
	return (5);
}

int	add_ops(const char *input, t_list **head, int i)
{
	int						j;
	static int				idx;
	t_token					*op;
	static const char		*op_tab[7] = {"<<", ">>", "|", ">", "<", "$", NULL};

	j = 0;
	if (!i)
		idx = i;
	while (op_tab[j])
	{
		if (!ft_strncmp(input + i, op_tab[j], ft_strlen(op_tab[j])))
		{
			op = init_token(ft_strdup(op_tab[j]), i, idx, get_label(op_tab[j]));
			if ((*op_tab[j]) == '$')
			{
				find_var(op, (char *)input);
				expand(op);
			}
			ft_lstadd_back(head, ft_lstnew(op));
			idx++;
			return (ft_strlen(op_tab[j]) - 1);
		}
		j++;
	}
	return (0);
}

void	get_ops(const char *input, t_list **head)
{
	bool	single_q;
	bool	double_q;
	size_t	i;

	i = 0;
	single_q = false;
	double_q = false;
	while (input[i])
	{
		if (input[i] == '"')
			double_q = (double_q + 1) % 2;
		if (input[i] == '\'')
			single_q = (single_q + 1) % 2;
		if ((!single_q && !double_q) || (input[i] == '$' && double_q))
			i += add_ops(input, head, i);
		i++;
	}
}
