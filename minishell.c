/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/05 13:21:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_label(t_label label)
{
	printf("Operator: ");
	if (label == INFILE)
		printf("INFILE\n");
	if (label == OUTFILE)
		printf("OUTFILE\n");
	if (label == PIPE)
		printf("PIPE\n");
	if (label == OUTFILE_A)
		printf("OUTFILE (Append)\n");
	if (label == HEREDOC)
		printf("HEREDOC\n");
	if (label == UNKNOWN)
		printf("UNKNOWN\n");
}

void	print_nodes(void *n)
{
	t_token	*node;

	node = (t_token *)n;
	printf("-------------\n");
	printf("Node %d\n", node->idx);
	print_label(node->label);
	printf("Input: \"%s\"\n", node->str);
	printf("At idx %d\n", node->str_idx);
	printf("-------------\n");
	printf("\n");
}

void	free_token_str(void *n)
{
	t_token	*node;

	node = (t_token *)n;
	free((char *)node->str);
}

int	main(void)
{
	t_list		**head;
	char		*input;

	while (1)
	{
		head = malloc(sizeof(t_list *));
		*head = NULL;
		input = readline("minishell> ");
		add_history(input);
		get_ops(input, head);
		ft_lstiter(*head, print_nodes);
		ft_lstclear(head, free);
		free(head);
		free(input);
	}
	clear_history();
}
