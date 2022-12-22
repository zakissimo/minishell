/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:02:00 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/22 13:40:45 by zhabri           ###   ########.fr       */
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
	free(children_pid);
	clear_cmds();
	free(g_glob->cmds);
	free_op_list();
	ft_lstclear(g_glob->envp, free);
	free(g_glob->envp);
	free(g_glob->head);
	free(g_glob->input);
	free(g_glob);
	rl_clear_history();
}
