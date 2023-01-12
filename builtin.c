/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:49:26 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/12 15:27:17 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(char *cmd)
{
	int					i;
	char				**cmd_split;
	static const char	*builtins[8] = \
		{"echo", "cd", "export", "env", "unset", "exit", "pwd", NULL};

	i = 0;
	cmd_split = ft_split_quotes(cmd, " \t");
	while (cmd_split && cmd_split[0] && builtins[i])
	{
		if (!ft_strncmp(builtins[i], cmd_split[0], ft_strlen(builtins[i]) + 1))
		{
			free_tab(cmd_split);
			return (i);
		}
		i++;
	}
	printf("jsp: %s\n", cmd_split[0]);
	free_tab(cmd_split);
	return (-1);
}

void	init_builtin_tab(t_builtin *tab[7])
{
	tab[0] = echo;
	tab[1] = cd;
	tab[2] = export;
	tab[3] = env;
	tab[4] = unset;
	tab[5] = exit_child;
	tab[6] = pwd;
}

void	call_builtin(int built_in, t_cmd *cmd, int *pipes, int *children_pid)
{
	int			i;
	int			fd_out;
	t_builtin	*tab[7];

	init_builtin_tab(tab);
	if (cmd->fd_out != -3)
		fd_out = cmd->fd_out;
	else
	{
		if (cmd->cmd_idx % 2 == 0)
			fd_out = pipes[3];
		else
			fd_out = pipes[1];
	}
	i = -1;
	while (++i < 4)
		if (pipes[i] != fd_out)
			close(pipes[i]);
	free(children_pid);
	if (cmd->fd_in != -1 && cmd->fd_out != -1)
		tab[built_in](cmd->str, fd_out);
	clean_exit(NULL);
	exit(1);
}
