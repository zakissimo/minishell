/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:32:29 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/27 13:57:43 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>

// Problème quand on enchaîne les ctrl+C : la commande suivante n'est pas prise en compte

static void	handler(int sig)
{
	if (sig == SIGINT && !g_glob->in_child)
	{
		g_glob->sig_int = true;
		if (g_glob->here_doc)
		{
			close(STDIN_FILENO);
			printf("\n");
		}
		else
		{
			ft_putchar_fd('\n', 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		g_glob->exit_ret = 130;
	}
	else if (sig == SIGINT && g_glob->in_child)
	{
		g_glob->sig_int = true;
		ft_putchar_fd('\n', 1);
		g_glob->exit_ret = 130;
	}
	if (sig == SIGQUIT && !g_glob->in_child)
		ft_putstr_fd("\b\b  \b\b", 1);
	else if (sig == SIGQUIT && g_glob->in_child)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_glob->exit_ret = 131;
	}
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

void	change_sig_handling(char *cmd)
{
	char	**cmd_split;
	char	*sum;

	sum = NULL;
	cmd_split = ft_split(cmd, ' ');
	cmd_split[0] = get_path(cmd_split[0]);
	if (cmd_split[0] != NULL)
	{
		get_sum(cmd_split[0], &sum);
		if (ft_strncmp(sum, g_glob->minishell_sum, 41) == 0)
			init_sig_callbacks(42);
	}
}
