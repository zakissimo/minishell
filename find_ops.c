/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/28 09:26:55 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "ops.h"
#include <stdlib.h>

char		*g_op[6];

void	find_ops(const char *input, t_list **head)
{
	int			i;
	int			j;
	t_op		*op;
	t_cmd		*cmd;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (g_op[j])
		{
			if (!ft_strncmp(input + i, g_op[j], ft_strlen(g_op[j])))
			{
				op = malloc(sizeof(t_op));
				op->idx = i;
				op->op = g_op[j];
				ft_lstadd_back(head, ft_lstnew(op));
				i += ft_strlen(g_op[j]);
			}
			j++;
		}
		i++;
	}
}

void	find_cmds(const char *input, t_list **head)
{
	int		start;
	int		end;
	t_list	*curr;
	t_op	*node;

	curr = *head;
	while (curr)
	{
		node = (t_op *)curr->content;
		start = node->idx + ft_strlen(node->op);
		curr = curr->next;
		if (curr)
		{
			node = (t_op *)curr->content;
			end = node->idx;
			ft_printf("%s\n", ft_substr(input, start, end - start));
		}
	}
}

void	print_nodes(void *n)
{
	t_op	*node;

	node = (t_op *)n;
	ft_printf("Found %s at idx %d\n", node->op, node->idx);
}

int	main(void)
{
	int			i;
	int			j;
	t_list		**head;
	const char	input[] = "< echo lol ||rev|rev|rev| rev >> out > lol";

	i = 0;
	g_op[0] = "||";
	g_op[1] = "<";
	g_op[2] = ">>";
	g_op[3] = ">";
	g_op[4] = "|";
	g_op[5] = NULL;
	head = malloc(sizeof(t_list *));
	*head = NULL;
	find_ops(input, head);
	find_cmds(input, head);
	ft_lstiter(*head, print_nodes);
	ft_lstclear(head, free);
	free(head);
}
