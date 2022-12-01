/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:53:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/01 11:53:30 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_node(t_list *curr, char *tmp)
{
	t_list	*next;
	t_token	*new;

	next = curr->next;
	new = malloc(sizeof(t_token));
	new->label = CMD;
	new->str = tmp;
	curr->next = ft_lstnew(new);
	curr->next->next = next;
}

void	find_cmds(const char *input, t_list **head)
{
	int		start;
	char	*tmp;
	t_list	*prev;
	t_list	*curr;
	t_token	*node;

	curr = *head;
	while (curr)
	{
		node = (t_token *)curr->content;
		start = node->idx + ft_strlen(node->str);
		prev = curr;
		curr = curr->next;
		if (curr)
		{
			node = (t_token *)curr->content;
			tmp = ft_substr(input, start, node->idx - start);
			tmp = ft_strtrimf(tmp, " ");
			insert_node(prev, tmp);
		}
	}
	if (curr)
	{
		tmp = ft_substr(input, start, ft_strlen(input) - start);
		tmp = ft_strtrimf(tmp, " ");
		insert_node(prev, tmp);
	}
	else
		insert_node(ft_lstnew((char *)input), (char *)input);
}
