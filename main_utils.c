/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:40:36 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/29 13:57:23 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_g_glob(void)
{
	g_glob->in_child = false;
	g_glob->sig_int = false;
	g_glob->sig_quit = false;
	g_glob->here_doc = false;
}

void	final_clean_up(void)
{
	ft_lstclear(g_glob->envp, free);
	free_null(g_glob->minishell_sum);
	free_null(g_glob->envp);
	free_null(g_glob);
	rl_clear_history();
}

void	free_null(void *var)
{
	if (var)
		free(var);
	var = NULL;
}

void	init_g_glob(void)
{
	g_glob = malloc(sizeof(t_glob));
	g_glob->head = NULL;
	g_glob->cmds = NULL;
	g_glob->envp = NULL;
	g_glob->input = NULL;
	g_glob->minishell_sum = NULL;
	g_glob->exit_ret = 0;
	g_glob->in_child = false;
	g_glob->sig_int = false;
	g_glob->here_doc = false;
}
