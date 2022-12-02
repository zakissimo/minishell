/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:53:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/02 09:31:33 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_node(t_list **curr, char *tmp)
{
	t_list	*next;
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->label = UNKNOWN;
	new->str = tmp;
	if (!*curr)
		ft_lstadd_back(curr, ft_lstnew(new));
	else
	{
		next = (*curr)->next;
		(*curr)->next = ft_lstnew(new);
		(*curr)->next->next = next;
	}
}

void	find_cmds(const char *input, t_list **head)
{
	if (!*head)
		insert_node(head, ft_strdup(input));
}
