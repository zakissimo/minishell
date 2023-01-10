/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:35:44 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/10 09:59:28 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup_and_close(t_cmd *cmd, int *pipes);

void	free_tab_bis(void *t)
{
	int		i;
	char	**tab;

	i = 1;
	tab = (char **)t;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	child(t_cmd *cmd, int *pipes, int *children_pid)
{
	char	**envp;
	char	**cmd_split;

	g_glob->exit_ret = 1;
	if (cmd->fd_in != -1 && cmd->fd_out != -1 && cmd->str[0] != '\0')
	{
		cmd_split = ft_split_quotes(cmd->str, " \t");
		cmd_split[0] = remove_quotes(cmd_split[0]);
		cmd_split[0] = get_path(cmd_split[0], false);
		exit_on_error(cmd, cmd_split, pipes, children_pid);
		dup_and_close(cmd, pipes);
		envp = envp_list_to_tab();
		clean_exit(children_pid);
		execve(cmd_split[0], cmd_split, envp);
		close_pipes(pipes);
		exit(g_glob->exit_ret);
	}
	close_pipes(pipes);
	if (cmd->fd_in != -1 || cmd->fd_out != -1)
	{
		clean_exit(children_pid);
		exit(1);
	}
	clean_exit(children_pid);
	exit(0);
}

static char	*get_path_loop(char *cmd, t_list *envp_entry)
{
	int		i;
	char	**paths;
	char	*cmd_absolute;

	i = 0;
	paths = NULL;
	if (envp_entry)
		paths = ft_split((char *)envp_entry->content + 5, ':');
	while (cmd != NULL && envp_entry && paths[i])
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

char	*get_path(char *cmd, bool shaone)
{
	t_list	*envp_entry;

	envp_entry = *g_glob->envp;
	while (envp_entry && \
		ft_strncmp((char *)envp_entry->content, "PATH=", 5))
		envp_entry = envp_entry->next;
	if (cmd && access(cmd, F_OK) == 0 && ft_strchr(cmd, '/'))
	{
		if (is_dir(cmd) && !shaone)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			g_glob->exit_ret = 126;
		}
		return (cmd);
	}
	return (get_path_loop(cmd, envp_entry));
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
