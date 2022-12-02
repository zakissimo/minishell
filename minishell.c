/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/02 10:52:40 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_nodes(void *n)
{
	t_token	*node;

	node = (t_token *)n;
	printf("-------------\n");
	printf("Input: \"%s\"\n", node->str);
	printf("At idx %d\n", node->idx);
	printf("-------------\n");
	printf("\n");
}

int	main(void)
{
	t_list		**head;
	char		input[] = "asdf | lol";

	// while (1)
	// {
	head = malloc(sizeof(t_list *));
	*head = NULL;
	// input = readline("minishell> ");
	find_ops(input, head);
	find_cmds(input, head);
	ft_lstiter(*head, print_nodes);
	ft_lstclear(head, free);
	free(head);
		// free(input);
	// }
}
