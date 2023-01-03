/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 10:49:26 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/03 13:16:55 by zhabri           ###   ########.fr       */
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
	cmd_split = ft_split_sep(cmd, " \t");
	while (cmd_split[0] && builtins[i])
	{
		if (!ft_strncmp(builtins[i], cmd_split[0], ft_strlen(builtins[i]) + 1))
		{
			free_tab(cmd_split);
			return (i);
		}
		i++;
	}
	free_tab(cmd_split);
	return (-1);
}

void	call_builtin(int built_in, t_cmd *cmd)
{
	t_builtin	*tab[7];

	tab[0] = echo;
	tab[1] = cd;
	tab[5] = exit_child;
	tab[6] = pwd;
	if (cmd->fd_out != -3)
		tab[built_in](cmd->str);
}
