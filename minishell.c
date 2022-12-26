/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/26 15:38:03 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_glob	*g_glob;

void	get_envp(char **envp)
{
	g_glob = malloc(sizeof(t_glob));
	if (g_glob)
		g_glob->envp = str_tab_to_list(envp);
}

void	get_head(t_list **head)
{
	*head = NULL;
	g_glob->head = head;
}

void	events(t_list **head)
{
	get_ops(g_glob->input, head);
	get_after_op();
	free_op_list();
	get_ops(g_glob->input, head);
	if (!op_error())
	{
		get_args();
		if (!pipe_error())
		{
			scan_heredocs();
			get_cmd();
			pipex();
			unlink_heredocs();
			clear_cmds();
			if (g_glob->cmds)
				free(g_glob->cmds);
		}
	}
	free_op_list();
}

void	event_loop(void)
{
	t_list				**head;
	char				*input;

	while (1)
	{
		g_glob->exit_ret = 0;
		g_glob->in_child = false;
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input == '\0')
			continue ;
		head = NULL;
		head = malloc(sizeof(t_list *));
		get_head(head);
		g_glob->input = input;
		add_history(input);
		if (head && !quote_error(input))
			events(head);
		free(g_glob->input);
		free(g_glob->head);
	}
}

int	main(int argc, char **argv, char **envp)
{
	init_sig_callbacks(PARENT);
	if (argc > 1)
		init_input(argv[1]);
	get_envp(envp);
	event_loop();
	final_clean_up();
}
