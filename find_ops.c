/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:39:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/28 20:17:51 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

char		*g_op[6];

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

void	find_ops(const char *input, t_list **head)
{
	int			i;
	int			j;
	t_token		*op;

	i = 0;
	while (input[i])
	{
		j = 0;
		while (g_op[j])
		{
			if (!ft_strncmp(input + i, g_op[j], ft_strlen(g_op[j])))
			{
				op = malloc(sizeof(t_token));
				op->idx = i;
				op->str = g_op[j];
				op->label = OP;
				ft_lstadd_back(head, ft_lstnew(op));
				i += ft_strlen(g_op[j]);
			}
			j++;
		}
		if (input[i] == '"' || input[i] == '\'')
			i += find_quote(input + i + 1, input[i]);
		i++;
	}
}

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
	tmp = ft_substr(input, start, ft_strlen(input) - start);
	tmp = ft_strtrimf(tmp, " ");
	insert_node(prev, tmp);
}

void	print_nodes(void *n)
{
	t_token	*node;

	node = (t_token *)n;
	ft_printf("Found %s at idx %d\n", node->str, node->idx);
}

int	main(void)
{
	t_list		**head;
	const char	input[] = "< echo lol ||\"rev||rev\"|'rev| rev' >> out > lol";

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
