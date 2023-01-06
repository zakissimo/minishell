/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:56:08 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/05 14:47:53 by zhabri           ###   ########.fr       */
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
	char	**cmd_split;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_quotes(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (cmd_split && cmd_split[0] && !ft_strncmp(cmd_split[0], "exit", 5))
		{
			ft_putstr_fd("exit\n", 1);
			if (exit_parent_arg(cmd_split))
			{
				free_tab(cmd_split);
				return (true);
			}
			else
			{
				clean_and_free(cmd_split);
				exit(g_glob->exit_ret);
			}
		}
		free_tab(cmd_split);
	}
	return (false);
}

void	exit_child(char *cmd, int fd_out)
{
	long long	ret;
	char		**cmd_split;

	close(fd_out);
	cmd_split = ft_split_quotes(cmd, " \t");
	if (cmd_split[1])
	{
		if (check_exit_error(cmd_split))
		{
			clean_and_free(cmd_split);
			exit(1);
		}
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
	clean_and_free(cmd_split);
	exit(g_glob->exit_ret);
}
