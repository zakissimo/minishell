/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:20:17 by brenaudo          #+#    #+#             */
/*   Updated: 2022/12/29 11:23:02 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sha1sum_child(char *cmd, int *pipefd, int *pipes);

void	get_sum(char *cmd, char **ret, int *pipes)
{
	int		fid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		perror("minishell:");
	fid = fork();
	if (fid == -1)
		perror("fork");
	else if (fid == 0)
		sha1sum_child(cmd, pipefd, pipes);
	close(pipefd[1]);
	waitpid(fid, NULL, 0);
	free(*ret);
	*ret = ft_calloc(41, sizeof(char));
	read(pipefd[0], *ret, 40);
	close(pipefd[0]);
}

static void	sha1sum_child(char *cmd, int *pipefd, int *pipes)
{
	int		i;
	char	*exec_args[3];
	char	**envp;

	i = -1;
	while (pipes && ++i < 4)
		close(pipes[i]);
	exec_args[0] = ft_strdup("/usr/bin/sha1sum");
	exec_args[1] = cmd;
	exec_args[2] = NULL;
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	envp = envp_list_to_tab();
	clean_exit(NULL);
	if (execve(exec_args[0], exec_args, envp) == -1)
		perror("minishell:");
	exit(1);
}
