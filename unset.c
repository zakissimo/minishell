/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:31:23 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/12 13:10:50 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_identifier(char *identifier)
{
	int		i;
	char	*err;

	i = 1;
	if (!ft_isalpha(identifier[0]) && identifier[0] != '_')
	{
		err = ft_strjoin("minishell: unset: ", identifier);
		err = ft_strjoinf(err, ": not a valid identifier\n");
		ft_putstr_fd(err, 2);
		free(err);
		return (false);
	}
	while (identifier[i])
	{
		if (!ft_isalnum(identifier[i]) && identifier[i] != '_')
		{
			err = ft_strjoin("minishell: unset: ", identifier);
			err = ft_strjoinf(err, ": not a valid identifier\n");
			ft_putstr_fd(err, 2);
			free(err);
			return (false);
		}	
		i++;
	}
	return (true);
}

void	unset_parent_arg(char **cmd_split, int index)
{
	char	*name;
	t_list	*env_cpy;
	t_list	*tmp;

	env_cpy = *g_glob->envp;
	name = ft_strjoin(cmd_split[index], "=");
	if (env_cpy->next == NULL \
		&& !ft_strncmp(env_cpy->content, name, ft_strlen(name)) \
		&& !ft_strncmp(env_cpy->content, cmd_split[index], \
			ft_strlen(cmd_split[index]) + 1))
		return (ft_lstdelone(env_cpy, free));
	while (env_cpy && env_cpy->next \
		&& ft_strncmp(env_cpy->next->content, name, ft_strlen(name))
		&& ft_strncmp(env_cpy->next->content, cmd_split[index], \
			ft_strlen(cmd_split[index]) + 1))
		env_cpy = env_cpy->next;
	tmp = env_cpy->next;
	if (tmp != NULL)
	{
		env_cpy->next = tmp->next;
		ft_lstdelone(tmp, free);
	}	
	g_glob->exit_ret = 0;
	free(name);
}

bool	unset_parent(void)
{
	int		i;
	char	**cmd_split;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_quotes(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (cmd_split && cmd_split[0] && !ft_strncmp(cmd_split[0], "unset", 6))
		{
			i = 0;
			while (cmd_split[++i])
				if (is_valid_identifier(cmd_split[i]))
					unset_parent_arg(cmd_split, i);
			free_tab(cmd_split);
			return (true);
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
