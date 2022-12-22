/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:49:37 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/22 15:13:38 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/includes/libft.h"
#include <readline/readline.h>

t_glob	*g_glob;

void	init_glob(char **envp)
{
	g_glob = malloc(sizeof(t_glob));
	if (g_glob)
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
		if (!pipe_error())
		{
			scan_heredocs();
			get_cmd();
			print_cmds();
			pipex();
			unlink_heredocs();
			ft_lstiter(*head, print_nodes);
			clear_cmds();
			if (g_glob->cmds)
				free(g_glob->cmds);
		}
	}
	free_op_list();
}

void	handle_sigint(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_redisplay();
		ft_putstr_fd("minishell> ", 1);
	}
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_list				**head;
	char				*input;
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	head = NULL;
	if (argc > 1)
		init_input(argv[1]);
	init_glob(envp);
	while (g_glob)
	{
		input = readline("minishell> ");
		if (input == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (*input == '\0')
			continue ;
		add_history(input);
		head = malloc(sizeof(t_list *));
		set_glob(head, input);
		if (head && !quote_error(input))
			events(head);
		free(g_glob->input);
		if (head)
		{
			free(head);
			head = NULL;
		}
	}
	if (head)
		free(head);
	ft_lstclear(g_glob->envp, free);
	free(g_glob->envp);
	free(g_glob);
	rl_clear_history();
}
