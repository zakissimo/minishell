/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:02:00 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/09 13:49:05 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_on_not_existing_file(char *cmd, char **cmd_split, \
		int *pipes, int *children_pid)
{
	char	**cmd_split_bis;

	cmd_split_bis = ft_split_quotes(cmd, " \t");
	if (cmd_split[0] == NULL && ft_strchr(cmd, '/') && \
		access(cmd_split_bis[0], F_OK) != 0)
	{
		ft_putstr_fd(cmd_split[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_tab(cmd_split);
		free_tab(cmd_split_bis);
		close_pipes(pipes);
		clean_exit(children_pid);
		exit(127);
	}
	free_tab(cmd_split_bis);
}

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
		ft_putstr_fd(cmd_split[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_tab(cmd_split);
		close_pipes(pipes);
		clean_exit(children_pid);
		exit(126);
	}
}

void	print_cmd_not_found(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
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
