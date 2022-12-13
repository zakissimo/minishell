/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/13 14:25:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/includes/libft.h"

t_glob	*g_glob;

void	init_glob(char **envp)
{
	g_glob = malloc(sizeof(t_glob));
	g_glob->envp = str_tab_to_list(envp);
}

void	set_glob(t_list **head, char *input)
{
	*head = NULL;
	g_glob->head = head;
	g_glob->input = input;
}

void	events(t_list **head)
{
	get_ops(g_glob->input, head);
	get_after_op();
	free_op_list();
	get_ops(g_glob->input, head);
	if (!op_error())
	{
		printf("New input: %s\n", g_glob->input);
		get_args();
		get_cmd();
		split_cmds();
		print_cmds();
		ft_lstiter(*head, print_nodes);
		clear_cmds();
		free(g_glob->cmds);
	}
	free_op_list();
}

int	main(int argc, char **argv, char **envp)
{
	t_list		**head;
	char		*input;

	(void)argc;
	(void)argv;
	init_glob(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input == '\0')
			continue ;
		add_history(input);
		head = malloc(sizeof(t_list *));
		set_glob(head, input);
		if (!quote_error(input))
			events(head);
		free(g_glob->input);
		free(head);
	}
	ft_lstclear(g_glob->envp, free);
	free(g_glob);
	clear_history();
}
