/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:32:29 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/10 11:11:47 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handler(int sig)
{
	if (sig == SIGINT)
		handle_sigint();
	else if (sig == SIGQUIT)
		handle_sigquit();
}

void	ignore_sig(int sig)
{
	(void)sig;
}

void	init_sig_callbacks(int process)
{
	if (process == 0)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
	}
	else
	{
		signal(SIGINT, ignore_sig);
		signal(SIGQUIT, ignore_sig);
	}
}

void	change_sig_handling(char *cmd, int *pipes, int *children_pid)
{
	char	**cmd_split;
	char	*sum;

	sum = NULL;
	if (cmd)
	{
		if (cmd[0])
		{
			cmd_split = ft_split_sep(cmd, " \t");
			cmd_split[0] = get_path(cmd_split[0], true);
			if (cmd_split[0] != NULL)
			{
				get_sum(cmd_split, &sum, pipes, children_pid);
				if (ft_strncmp(sum, g_glob->minishell_sum, 41) == 0)
					init_sig_callbacks(42);
				free(sum);
			}
			if (cmd_split[0])
				free_tab(cmd_split);
			else
				free_tab_bis(cmd_split);
		}
	}
}
