/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:02:33 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/09 15:54:11 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <sys/wait.h>

static void	create_pipes(int *pipes);
static void	close_pipe_and_recreate(int	*pipes, t_cmd *cmd);

static void	pipex_loop_core(int	*children_pid, t_list *curr, int *pipes)
{
	// int		ret;
	int		built_in;

	built_in = builtin(((t_cmd *)curr->content)->str);
	children_pid[((t_cmd *)curr->content)->cmd_idx] = fork();
	if (children_pid[((t_cmd *)curr->content)->cmd_idx] == 0)
	{
		if (built_in == -1)
			child(((t_cmd *)curr->content), pipes, children_pid);
		else
			call_builtin(built_in, ((t_cmd *)curr->content), pipes, \
				children_pid);
	}
	if (built_in == -1)
		change_sig_handling(((t_cmd *)curr->content)->str, pipes);
	// else
	// {
	// 	waitpid(children_pid[((t_cmd *)curr->content)->cmd_idx], &ret, 0);
	// 	printf("children_pid is %d, ret is %d\n", children_pid[((t_cmd *)curr->content)->cmd_idx], ret >> 8);
	// 	if (ret >> 8 == 0)
	// 		children_pid[((t_cmd *)curr->content)->cmd_idx] = -256;
	// 	else
	// 		children_pid[((t_cmd *)curr->content)->cmd_idx] = -1 * (ret >> 8);
	// }
	g_glob->in_child = true;
	close_pipe_and_recreate(pipes, ((t_cmd *)curr->content));
}

int	*pipex_loop(void)
{
	int		pipes[4];
	int		*children_pid;
	t_list	*curr;

	curr = *g_glob->cmds;
	init_children_pid(&children_pid, ft_lstsize(curr) + 1);
	create_pipes(pipes);
	while (curr)
	{
		if (curr->content)
			pipex_loop_core(children_pid, curr, pipes);
		curr = curr->next;
	}
	close_pipes(pipes);
	return (children_pid);
}

void	pipex(void)
{
	int		i;
	int		exit_ret;
	int		*children_pid;

	i = 0;
	if (exit_parent() || cd_parent() || unset_parent() || export_parent())
		return ;
	children_pid = pipex_loop();
	while (children_pid[i] != 0)
	{
		// printf("children_pid: %d\n", children_pid[i]);
		// if (children_pid[i] < 0 && !g_glob->sig_int && !g_glob->sig_quit \
		// 	&& children_pid[i] != -256)
		// 	g_glob->exit_ret = children_pid[i] * (-1);
		// else if (children_pid[i] < 0 && !g_glob->sig_int && !g_glob->sig_quit \
		// 	&& children_pid[i] == -256)
		// 	g_glob->exit_ret = 0;
		// else if (children_pid[i] > 0)
		// {
			waitpid(children_pid[i], &exit_ret, 0);
			// printf("ret is %d\n", exit_ret >> 8);
			if (!g_glob->sig_int && !g_glob->sig_quit)
				g_glob->exit_ret = exit_ret >> 8;
		// }
		i++;
	}
	g_glob->in_child = false;
	init_sig_callbacks(0);
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
