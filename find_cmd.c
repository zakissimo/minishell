/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:53:10 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/02 12:15:23 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

t_token	*init_token(char *str, int idx)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->idx = idx;
	new->label = UNKNOWN;
	new->str = str;
	return (new);
}

void	clean_and_insert(t_list **head, char *tmp, int start, int i)
{
	//count leading spaces
	tmp = ft_strtrimf(tmp, " ");
	insert_node(head, ft_lstnew(init_token(tmp, start)), i); //add len of leading spaces to start
}

void	find_cmds(const char *input, t_list **head)
{
	int		i;
	int		start;
	char	*tmp;
	t_list	*curr;
	t_token	*node;

	i = 0;
	start = 0;
	curr = *head;
	while (curr)
	{
		node = (t_token *)curr->content;
		if (curr)
		{
			tmp = ft_substr(input, start, node->idx - start);
			tmp = ft_strtrimf(tmp, " ");
			insert_node(head, ft_lstnew(init_token(tmp, start)), i);
			i++;
		}
		curr = curr->next;
		start += node->idx + ft_strlen(node->str);
		i++;
	}
	tmp = ft_substr(input, start, node->idx - start);
	tmp = ft_strtrimf(tmp, " ");
	insert_node(head, ft_lstnew(init_token(tmp, start)), i);
}
