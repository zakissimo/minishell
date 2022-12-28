/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:20:17 by brenaudo          #+#    #+#             */
/*   Updated: 2022/12/28 12:20:31 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sha1sum_child(char *cmd, int *pipe);

void	get_sum(char *cmd, char **ret)
{
	int		fid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		perror("minishell:");
	fid = fork();
	if (fid == -1)
		perror("fork");
	else if (fid == 0)
		sha1sum_child(cmd, pipefd);
	close(pipefd[1]);
	waitpid(fid, NULL, 0);
	free(*ret);
	*ret = ft_calloc(41, sizeof(char));
	read(pipefd[0], *ret, 40);
	close(pipefd[0]);
}

static void	sha1sum_child(char *cmd, int *pipefd)
{
	char	*exec_args[3];
	char	**envp;

	exec_args[0] = ft_strdup("/usr/bin/sha1sum");
	exec_args[1] = cmd;
	exec_args[2] = NULL;
	close(pipefd[0]);
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	envp = envp_list_to_tab();
	free(g_glob->minishell_sum);
	clean_exit(NULL);
	if (execve(exec_args[0], exec_args, envp) == -1)
		perror("minishell:");
	exit(1);
}
