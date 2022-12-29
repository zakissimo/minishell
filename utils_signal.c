/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 14:02:56 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/29 14:04:20 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(void)
{
	if (!g_glob->in_child)
	{
		if (g_glob->here_doc)
		{
			g_glob->sig_int = true;
			close(STDIN_FILENO);
			ft_putchar_fd('\n', 1);
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
	else if (g_glob->in_child)
	{
		g_glob->sig_int = true;
		ft_putchar_fd('\n', 1);
		g_glob->exit_ret = 130;
	}
}

void	handle_sigquit(void)
{
	if (!g_glob->in_child)
		ft_putstr_fd("\b\b  \b\b", 1);
	else if (g_glob->in_child)
	{
		g_glob->sig_quit = true;
		ft_putstr_fd("Quit (core dumped)\n", 2);
		g_glob->exit_ret = 131;
	}
}
