/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/28 07:45:03 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "ops.h"

void	find_op(const char *input, const char *op, t_list **head, bool reset)
{
	static int	idx;
	char		*sub_input;
	t_op		*node;

	if (reset)
		idx = -1;
	sub_input = ft_strnstr(input, op, ft_strlen(input));
	if (sub_input)
	{
		idx += ft_strlen(input) - ft_strlen(sub_input) + ft_strlen(op);
		node = malloc(sizeof(t_op));
		node->idx = idx;
		if (ft_strlen(op) > 1)
			node->idx -= ft_strlen(op) - 1;
		node->op = op;
		ft_lstadd_back(head, ft_lstnew(node));
		find_op(sub_input + ft_strlen(op), op, head, false);
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
	t_list		**head;
	char		*op[6];
	const char	input[] = ">>>e>cho lol ||rev|rev|rev| rev >> out > lol";

	op[0] = "|";
	op[1] = "<";
	op[2] = ">>>";
	op[3] = ">";
	op[4] = "||";
	op[5] = NULL;
	i = 0;
	head = malloc(sizeof(t_list *));
	*head = NULL;
	while (op[i])
	{
		find_op(input, op[i], head, true);
		i++;
	}
	ft_lstiter(*head, print_nodes);
	ft_lstclear(head, free);
	free(head);
}
