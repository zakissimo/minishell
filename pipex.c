/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:02:33 by brenaudo          #+#    #+#             */
/*   Updated: 2022/12/26 15:23:31 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static void	create_pipes(int *pipes);
static void	close_pipe_and_recreate(int	*pipes, t_cmd *cmd);

int	*pipex_loop(void)
{
	int		pipes[4];
	int		*children_pid;
	t_list	*curr;
	t_cmd	*cmd;

	curr = *g_glob->cmds;
	children_pid = NULL;
	while (!children_pid)
		children_pid = ft_calloc(ft_lstsize(curr) + 1, sizeof(int));
	create_pipes(pipes);
	while (curr)
	{
		if (curr->content)
		{
			cmd = ((t_cmd *)curr->content);
			children_pid[cmd->cmd_idx] = fork();
			if (children_pid[cmd->cmd_idx] == 0)
				child(cmd, pipes, children_pid);
			g_glob->in_child = true;
			close_pipe_and_recreate(pipes, cmd);
			curr = curr->next;
		}
	}
	close_pipes(pipes);
	return (children_pid);
}

void	pipex(void)
{
	int		i;
	int		*children_pid;

	i = 0;
	children_pid = pipex_loop();
	while (children_pid[i] != 0)
		waitpid(children_pid[i++], NULL, 0);
	g_glob->in_child = false;
	free(children_pid);
}

static void	create_pipes(int *pipes)
{
	pipe(pipes);
	pipe(pipes + 2);
}

static void	close_pipe_and_recreate(int	*pipes, t_cmd *cmd)
{
	if (cmd->cmd_idx % 2 == 0)
	{
		if (pipes[0] > 2)
			close(pipes[0]);
		if (pipes[1] > 2)
			close(pipes[1]);
		pipe(pipes);
	}
	else
	{
		if (pipes[2] > 2)
			close(pipes[2]);
		if (pipes[3] > 2)
			close(pipes[3]);
		pipe(pipes + 2);
	}
}
