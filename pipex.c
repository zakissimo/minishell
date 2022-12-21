/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:02:33 by brenaudo          #+#    #+#             */
/*   Updated: 2022/12/21 12:02:50 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pipes(int *pipes);
static void	close_pipe_and_recreate(int	*pipes, t_cmd *cmd);

void	pipex(void)
{
	int		i;
	int		pipes[4];
	int		*children_pid;
	t_list	*curr;
	t_cmd	*cmd;

	curr = *g_glob->cmds;
	children_pid = ft_calloc(ft_lstsize(curr) + 1, sizeof(int)); //malloc pas protégé
	create_pipes(pipes);
	while (curr)
	{
		if (curr->content)
		{
			cmd = ((t_cmd *)curr->content);
			children_pid[cmd->cmd_idx] = fork();
			if (children_pid[cmd->cmd_idx] == 0)
				child(cmd, pipes);
			close_pipe_and_recreate(pipes, cmd);
			curr = curr->next;
		}
	}
	i = 0;
	while (children_pid[i] != 0)
		waitpid(children_pid[i++], NULL, 0);
	close_pipes(pipes);
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

void	clean_exit(void)
{
	clear_cmds();
	free(g_glob->cmds);
	free_op_list();
}
