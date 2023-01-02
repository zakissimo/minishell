/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:56:08 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/02 15:02:43 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

bool	exit_parent_arg(char **cmd_split)
{
	long long	ret;

	if (cmd_split[1])
	{
		if (check_exit_error(cmd_split))
			return (true);
		clean_exit(NULL);
		if (!is_valid_exit_arg(cmd_split[1]))
		{
			free_tab(cmd_split);
			exit(2);
		}
		ret = ft_atoll(cmd_split[1]);
		free_tab(cmd_split);
		exit(ret);
	}
	return (false);
}

bool	exit_parent(void)
{
	char		**cmd_split;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_sep(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (!ft_strncmp(cmd_split[0], "exit", 5))
		{
			ft_putstr_fd("exit\n", 2);
			if (exit_parent_arg(cmd_split))
				return (true);
			else
			{
				clean_exit(NULL);
				free_tab(cmd_split);
				exit(0);
			}
		}
	}
	return (false);
}

bool	exit_child_arg(char **cmd_split)
{
	long long	ret;

	if (cmd_split[1])
	{
		if (check_exit_error(cmd_split))
			return (true);
		if (!is_valid_exit_arg(cmd_split[1]))
		{
			free_tab(cmd_split);
			g_glob->exit_ret = 2;
		}
		ret = ft_atoll(cmd_split[1]);
		g_glob->exit_ret = ret;
	}
	free_tab(cmd_split);
	return (false);
}

bool	exit_child(char *cmd)
{
	char		**cmd_split;

	cmd_split = ft_split_sep(cmd, " \t");
	if (!ft_strncmp(cmd_split[0], "exit", 5))
	{
		g_glob->exit_ret = 0;
		exit_child_arg(cmd_split);
		return (true);
	}
	return (false);
}
