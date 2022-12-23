/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:32:29 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/23 10:36:41 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_redisplay();
		ft_putstr_fd("minishell> ", 1);
	}
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void	init_sig_callbacks(void)
{
	signal(SIGINT, parent_handler_sigint);
	signal(SIGQUIT, parent_handler_sigint);
}
