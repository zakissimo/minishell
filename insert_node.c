/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:24:31 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/02 11:42:13 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_node(t_list **head, t_list *node, int idx)
{
	t_list	*curr;
	t_list	*next;
	int		i;

	if (!*head)
		ft_lstadd_back(head, node);
	else if (!idx)
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
	}
}
