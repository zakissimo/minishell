/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:32:29 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/26 14:43:59 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static void	handler(int sig)
{
	if (sig == SIGINT && !g_glob->in_child)
	{
		ft_putchar_fd('\n', 1);
		ft_putstr_fd("minishell> ", 1);
	}
	else if (sig == SIGINT && g_glob->in_child)
		ft_putchar_fd('\n', 1);
	if (sig == SIGQUIT && !g_glob->in_child)
		ft_putstr_fd("\b\b  \b\b", 1);
	else if (sig == SIGQUIT && g_glob->in_child)
		ft_putstr_fd("Quit (core dumped)\n", 2);
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
