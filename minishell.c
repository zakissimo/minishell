/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/06 14:26:09 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (quote_error(input) || op_error(input))
			free(input);
		else
		{
			get_ops(input, head);
			ft_lstiter(*head, print_nodes);
			ft_lstiter(*head, free_token_str);
			ft_lstclear(head, free);
			free(head);
			free(input);
		}
	}
	clear_history();
}
