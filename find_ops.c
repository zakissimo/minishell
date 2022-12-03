/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/03 16:38:29 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"
#include <stddef.h>

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

t_token	*init_token(char *str, int str_idx, int idx, t_label label)
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
	int		j;
	int		n;
	t_token	*op;
	char	*op_tab[6];

	op_tab[0] = "||";
	op_tab[1] = "<";
	op_tab[2] = ">>";
	op_tab[3] = ">";
	op_tab[4] = "|";
	op_tab[5] = NULL;
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

void	add_cmd(const char *input, size_t i, size_t end_cmd)
{
	char			*tmp;
	static size_t	start_cmd;

	if (!end_cmd)
		start_cmd = end_cmd;
	if (end_cmd < i || i == ft_strlen(input) - 1)
	{
		tmp = ft_substr(input, start_cmd, end_cmd - start_cmd);
		printf("%s\n", tmp);
		printf("i %zu, start_cmd %zu, end_cmd %zu\n", i, start_cmd, end_cmd);
		start_cmd = i;
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
		add_cmd(input, i, end_cmd);
		if (input[i] == '"' || input[i] == '\'')
			i += find_quote(input + i + 1, input[i]);
		i++;
	}
}
