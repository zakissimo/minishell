/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:35:14 by brenaudo          #+#    #+#             */
/*   Updated: 2022/12/22 13:43:38 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static char	*get_path(char *cmd);
static void	dup_and_close(t_cmd *cmd, int *pipes);

static void	free_tab_bis(void *t)
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

	if (cmd->fd_in != -1 && cmd->fd_out != -1 && cmd->str[0] != '\0')
	{
		cmd_split = ft_split(cmd->str, ' ');
		cmd_split[0] = get_path(cmd_split[0]);
		if (cmd_split[0] == NULL)
		{
			free_tab_bis(cmd_split);
			close_pipes(pipes);
			print_cmd_not_found(cmd->str);
			clean_exit(children_pid);
			exit(127);
		}
		dup_and_close(cmd, pipes);
		envp = envp_list_to_tab();
		clean_exit(children_pid);
		if (execve(cmd_split[0], cmd_split, envp) == -1)
			perror("Error");
	}
	else
		clean_exit(children_pid);
	close_pipes(pipes);
	exit(1);
}

static char	*get_path_loop(char *cmd, t_list *envp_entry)
{
	int		i;
	char	**paths;
	char	*cmd_absolute;

	i = 0;
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

static char	*get_path(char *cmd)
{
	t_list	*envp_entry;

	envp_entry = *g_glob->envp;
	while (ft_strncmp((char *)envp_entry->content, "PATH=", 5))
		envp_entry = envp_entry->next;
	if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
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