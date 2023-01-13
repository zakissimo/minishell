/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 13:24:09 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/13 11:51:51 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_on_error(t_cmd *cmd, char **cmd_split, \
		int *pipes, int *children_pid)
{
	exit_on_not_existing_file(cmd->str, cmd_split, pipes, children_pid);
	exit_on_bad_cmd(cmd_split, pipes, cmd->str, children_pid);
	exit_on_permission(cmd_split, pipes, children_pid);
}

void	init_children_pid(int **children_pid, int size)
{
	*children_pid = NULL;
	while (!*children_pid)
		*children_pid = ft_calloc(size, sizeof(int));
}

void	pipex_handle_exit_ret(int children_pid, int exit_ret)
{
	if (g_glob->sig_int)
		g_glob->exit_ret = 130;
	else if (g_glob->sig_quit)
		g_glob->exit_ret = 131;
	else
	{
		if (children_pid < 0 && children_pid != -256)
			g_glob->exit_ret = children_pid * (-1);
		else if (children_pid < 0 && children_pid == -256)
			g_glob->exit_ret = 0;
		else if (children_pid > 0)
			g_glob->exit_ret = exit_ret >> 8;
	}
}
