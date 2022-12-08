/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/08 10:34:41 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	*g_glob;

void	init_glob(t_list **head, char *input, char **envp)
{
	g_glob = malloc(sizeof(t_glob));
	g_glob->head = head;
	g_glob->input = input;
	g_glob->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_list		**head;
	char		*input;

	(void)argc;
	(void)argv;
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
			init_glob(head, input, envp);
			get_ops(input, head);
			expand_input();
			ft_lstiter(*head, print_nodes);
			ft_lstiter(*head, free_token_str);
			ft_lstclear(head, free);
			free(head);
			free(input);
			free(g_glob);
		}
	}
	clear_history();
}
