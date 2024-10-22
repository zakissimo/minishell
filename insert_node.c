/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:24:31 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/04 12:56:20 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_idx(void *l)
{
	t_list	*list;
	t_token	*node;

	list = (t_list *)l;
	while (list)
	{
		node = (t_token *)list->content;
		node->idx++;
		list = list->next;
	}
}

void	insert_node(t_list **head, t_list *node, int idx)
{
	t_list	*curr;
	t_list	*next;
	int		i;

	ft_printf("lst_size %d, idx %d\n", ft_lstsize(*head), idx);
	if (!*head || idx >= ft_lstsize(*head))
		ft_lstadd_back(head, node);
	else if (idx <= 0)
		ft_lstadd_front(head, node);
	else
	{
		i = 0;
		curr = *head;
		while (curr && i < idx - 1)
		{
			i++;
			curr = curr->next;
		}
		next = curr->next;
		curr->next = node;
		node->next = next;
		ft_lstiter(next, &increment_idx);
	}
}
