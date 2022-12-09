/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/09 12:45:35 by zhabri           ###   ########.fr       */
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

void	events(t_list **head, char *input, char **envp)
{
	init_glob(head, input, envp);
	get_ops(g_glob->input, head);
	if (!op_error())
	{
		get_after_op();
		free_list();
		get_ops(g_glob->input, head);
		printf("%s\n", g_glob->input);
		get_args();
		ft_lstiter(*head, print_nodes);
	}
	free_list();
	nuke_glob();
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
		if (quote_error(input))
		{
			free(input);
			free(head);
		}
		else
			events(head, input, envp);
	}
	clear_history();
}
