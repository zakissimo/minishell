/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:31:23 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/03 11:51:39 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	unset_parent(void)
{
	char	*name;
	char	**cmd_split;
	t_list	*env_cpy;
	t_list	*tmp;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_sep(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (!ft_strncmp(cmd_split[0], "unset", 6))
		{
			if (cmd_split[1])
			{
				env_cpy = *g_glob->envp;
				name = ft_strjoin(cmd_split[1], "=");
				if (env_cpy->next == NULL && \
					!ft_strncmp(env_cpy->content, name, ft_strlen(name)))
				{
					ft_lstdelone(env_cpy, free);
					free_tab(cmd_split);
					return (true);
				}
				while (env_cpy && env_cpy->next && \
					ft_strncmp(env_cpy->next->content, name, ft_strlen(name)))
					env_cpy = env_cpy->next;
				tmp = env_cpy->next;
				env_cpy->next = tmp->next;
				ft_lstdelone(tmp, free);
				free_tab(cmd_split);
				g_glob->exit_ret = 0;
				return (true);
			}	
		}
		free_tab(cmd_split);
	}
	return (false);
}

void	unset(char *cmd, int fd_out)
{
	(void)cmd;
	close(fd_out);
	clean_exit(NULL);
	exit(0);
}
