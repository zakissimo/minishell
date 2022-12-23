/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:02:00 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/23 11:02:02 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_not_found(char *str)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
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

void	clean_exit(int *children_pid)
{
	free_null(children_pid);
	clear_cmds();
	free_null(g_glob->cmds);
	free_op_list();
	ft_lstclear(g_glob->envp, free);
	free_null(g_glob->envp);
	free_null(g_glob->head);
	free_null(g_glob->input);
	free_null(g_glob);
	rl_clear_history();
}
