/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/28 08:35:41 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "ops.h"

void	find_op(const char *input, t_list **head)
{
	int			i;
	int			j;
	t_op		*node;
	char		*op[6];

	op[0] = "||";
	op[1] = "<";
	op[2] = ">>";
	op[3] = ">";
	op[4] = "|";
	op[5] = NULL;
	i = 0;
	while (input[i])
	{
		j = 0;
		while (op[j])
		{
			if (!ft_strncmp(input + i, op[j], ft_strlen(op[j])))
			{
				node = malloc(sizeof(t_op));
				node->idx = i;
				node->op = op[j];
				ft_lstadd_back(head, ft_lstnew(node));
				i += ft_strlen(op[j]);
			}
			j++;
		}
		i++;
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
	const char	input[] = ">>>e>cho lol ||rev|rev|rev| rev >> out > lol";

	i = 0;
	head = malloc(sizeof(t_list *));
	*head = NULL;
	find_op(input, head);
	ft_lstiter(*head, print_nodes);
	ft_lstclear(head, free);
	free(head);
}
