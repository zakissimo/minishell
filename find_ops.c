/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/04 11:36:44 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"
#include <stddef.h>
#include <stdio.h>

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

int	add_ops(const char *input, t_list **head, int i)
{
	int						j;
	int						n;
	t_token					*op;
	static const char		*op_tab[6] = {"||", "<", ">>", ">", "|", NULL};

	j = 0;
	n = i;
	while (op_tab[j])
	{
		if (!ft_strncmp(input + i, op_tab[j], ft_strlen(op_tab[j])))
		{
			op = init_token(op_tab[j], i, 0, OP);
			ft_lstadd_back(head, ft_lstnew(op));
			i += ft_strlen(op_tab[j]);
		}
		j++;
	}
	return (i - n);
}

void	add_cmd(t_list **head, const char *input, size_t i, size_t end_cmd)
{
	t_token			*cmd;
	char			*tmp;
	static size_t	start_cmd;

	if (!end_cmd)
		start_cmd = end_cmd;
	if (end_cmd < i)
	{
		tmp = ft_substr(input, start_cmd, end_cmd - start_cmd);
		cmd = init_token(ft_strtrimf(tmp, " \t"), start_cmd, 0, UNKNOWN);
		start_cmd = i;
		// printf("%d\n", ft_lstsize(*head) - 2);
		// insert_node(head, ft_lstnew(cmd), ft_lstsize(*head) - 2);
		ft_lstadd_front(head, ft_lstnew(cmd));
	}
}

void	split_by_ops(const char *input, t_list **head)
{
	size_t	i;
	size_t	end_cmd;

	i = 0;
	while (input[i])
	{
		end_cmd = i;
		i += add_ops(input, head, i);
		add_cmd(head, input, i, end_cmd);
		if (input[i] == '"' || input[i] == '\'')
			i += find_quote(input + i + 1, input[i]);
		i++;
	}
	if (i)
		add_cmd(head, input, i + 1, i);
}
