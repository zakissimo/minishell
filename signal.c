/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:32:29 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/27 11:13:56 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static void	handler(int sig)
{
	if (sig == SIGINT && !g_glob->in_child)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_glob->exit_ret = 130;
	}
	else if (sig == SIGINT && g_glob->in_child)
	{
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
	(void)process;
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
}
