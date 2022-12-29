/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:02:00 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/29 11:09:49 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_on_bad_cmd(char **cmd_split, \
		int *pipes, char *cmd, int *children_pid)
{
	if (cmd_split[0] == NULL)
	{
		free_tab_bis(cmd_split);
		close_pipes(pipes);
		print_cmd_not_found(cmd);
		clean_exit(children_pid);
		exit(127);
	}
}

void	exit_on_permission(char **cmd_split, \
		int *pipes, int *children_pid)
{
	if (access(cmd_split[0], X_OK) != 0)
	{
		ft_putstr_fd("Permission denied: ", 2);
		ft_putstr_fd(cmd_split[0], 2);
		ft_putchar_fd('\n', 2);
		free_tab(cmd_split);
		close_pipes(pipes);
		clean_exit(children_pid);
		exit(126);
	}
}

void	print_cmd_not_found(char *str)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

void	close_pipes(int *pipes)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (pipes[i] > 2)
			close(pipes[i]);
	}
}

void	clean_exit(int *children_pid)
{
	free_null(children_pid);
	if (g_glob->cmds)
		clear_cmds();
	free_null(g_glob->cmds);
	if (g_glob->head)
		free_op_list();
	if (g_glob->envp)
		ft_lstclear(g_glob->envp, free);
	free_null(g_glob->envp);
	free_null(g_glob->head);
	free_null(g_glob->input);
	free_null(g_glob->minishell_sum);
	free_null(g_glob);
	rl_clear_history();
}
