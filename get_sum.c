/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:20:17 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/10 13:00:04 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sha1sum_child(char **cmd, int *pipefd, int *pipes, \
			int *children_pid);

void	get_sum(char **cmd, char **ret, int *pipes, int *children_pid)
{
	int		fid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		perror("minishell");
	fid = fork();
	if (fid == -1)
		perror("fork");
	else if (fid == 0)
		sha1sum_child(cmd, pipefd, pipes, children_pid);
	close(pipefd[1]);
	waitpid(fid, NULL, 0);
	free(*ret);
	*ret = ft_calloc(41, sizeof(char));
	read(pipefd[0], *ret, 40);
	close(pipefd[0]);
}

bool	is_dir(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir == NULL)
		return (false);
	closedir(dir);
	return (true);
}

static void	free_cmd_tab(char **cmd)
{
	if (cmd[0])
		free_tab(cmd);
	else
		free_tab_bis(cmd);
}

static void	sha1sum_free(char **cmd, char **envp, char *exec1, char *exec2)
{
	free_cmd_tab(cmd);
	free(exec1);
	free(exec2);
	free_tab(envp);
	close(1);
}

static void	sha1sum_child(char **cmd, int *pipefd, int *pipes, \
			int *children_pid)
{
	int		i;
	char	*exec_args[3];
	char	**envp;

	i = -1;
	if (children_pid != NULL)
		free(children_pid);
	while (pipes && ++i < 4)
		close(pipes[i]);
	exec_args[0] = ft_strdup("/usr/bin/sha1sum");
	exec_args[1] = ft_strdup(cmd[0]);
	exec_args[2] = NULL;
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	envp = envp_list_to_tab();
	clean_exit(NULL);
	if (!is_dir(cmd[0]) && !access(cmd[0], X_OK))
	{
		free_cmd_tab(cmd);
		execve(exec_args[0], exec_args, envp);
	}
	sha1sum_free(cmd, envp, exec_args[0], exec_args[1]);
	exit(1);
}
