/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:35:14 by brenaudo          #+#    #+#             */
/*   Updated: 2022/12/22 11:28:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *cmd);
static void	dup_and_close(t_cmd *cmd, int *pipes);
static int	ft_is_space(char c);

void	child(t_cmd *cmd, int *pipes)
{
	char	**cmd_split;

	if (cmd->fd_in != -1 && cmd->fd_out != -1)
	{
		cmd_split = ft_split(cmd->str, ' ');
		cmd_split[0] = get_path(cmd_split[0]);
		if (ft_is_space(cmd->str[0]) == 1 || cmd_split[0] == NULL)
		{
			free_tab(cmd_split);
			close_pipes(pipes);
			ft_putstr_fd("Command not found: ", 2);
			ft_putstr_fd(cmd->str, 2);
			ft_putstr_fd("\n", 2);
			clean_exit();
			exit(127);
		}
		dup_and_close(cmd, pipes);
		clean_exit();
		if (execve(cmd_split[0], cmd_split, envp_list_to_tab()) == -1)
			perror("Error");
	}
	else
		clean_exit();
	close_pipes(pipes);
	exit(1);
}

static char	*get_path(char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_absolute;
	t_list	*envp_entry;

	i = 0;
	envp_entry = *g_glob->envp;
	while (ft_strncmp((char *)envp_entry->content, "PATH=", 5))
		envp_entry = envp_entry->next;
	if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	paths = ft_split((char *)envp_entry->content + 5, ':');
	while (cmd != NULL && paths[i])
	{	
		cmd_absolute = ft_strjoin(paths[i], "/");
		cmd_absolute = ft_strjoinf(cmd_absolute, cmd);
		if (access(cmd_absolute, 0) == 0)
		{
			free_tab(paths);
			free(cmd);
			return (cmd_absolute);
		}
		free(cmd_absolute);
		i++;
	}
	free(cmd);
	free_tab(paths);
	return (NULL);
}

static void	dup_and_close(t_cmd *cmd, int *pipes)
{
	if (cmd->fd_in != -3 && cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, 0);
		close(cmd->fd_in);
	}
	else if (cmd->fd_in != 0)
	{
		if (cmd->cmd_idx % 2 == 0)
			dup2(pipes[0], 0);
		else
			dup2(pipes[2], 0);
	}
	if (cmd->fd_out != -3 && cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, 1);
		close(cmd->fd_out);
	}
	else if (cmd->fd_out != 1)
	{
		if (cmd->cmd_idx % 2 == 0)
			dup2(pipes[3], 1);
		else
			dup2(pipes[1], 1);
	}
	close_pipes(pipes);
}

static int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}
