/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:40:50 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/05 14:47:16 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env_node(char *var)
{
	char	*var_eq;
	t_list	*envp_entry;

	var_eq = ft_strjoin(var, "=");
	envp_entry = *g_glob->envp;
	while (envp_entry \
		&& ft_strncmp((char *)envp_entry->content, var_eq, ft_strlen(var_eq)) \
		&& ft_strncmp((char *)envp_entry->content, var, ft_strlen(var) + 1))
		envp_entry = envp_entry->next;
	free(var_eq);
	return (envp_entry);
}

static void	ft_chdir(char *dir, int size)
{
	char	*ret;
	char	*tmp;
	t_list	*pwd;
	t_list	*old_pwd;

	pwd = get_env_node("PWD");
	old_pwd = get_env_node("OLDPWD");
	ret = NULL;
	free_null(old_pwd->content);
	tmp = ft_strdup(pwd->content + 4);
	old_pwd->content = ft_strjoin("OLDPWD=", tmp);
	free_and_null(&tmp);
	chdir(dir);
	while (ret == NULL)
	{
		size *= 2;
		free_and_null(&tmp);
		while (tmp == NULL)
			tmp = ft_calloc(size, sizeof(char));
		ret = getcwd(tmp, size);
	}
	free_null(pwd->content);
	pwd->content = ft_strjoin("PWD=", tmp);
	free_null(tmp);
}

void	cd(char *cmd, int fd_out)
{
	char	**cmd_split;
	DIR		*dir;

	close(fd_out);
	cmd_split = ft_split_sep(cmd, " \t");
	if (cmd_split[1])
	{
		dir = opendir(cmd_split[1]);
		if (cmd_split[2] || !dir)
		{
			if (cmd_split[2])
				ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			if (!dir)
				print_error_dir_cd(cmd_split[1]);
			clean_and_free(cmd_split);
			exit(1);
		}
		closedir(dir);
		ft_chdir(cmd_split[1], 16);
	}
	else
		ft_chdir(get_env_node("HOME")->content + 5, 16);
	clean_and_free(cmd_split);
	exit(0);
}

bool	cd_parent_arg(char **cmd_split)
{
	DIR		*dir;

	dir = opendir(cmd_split[1]);
	if (cmd_split[2] || !dir)
	{
		if (cmd_split[2])
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		if (!dir)
			print_error_dir_cd(cmd_split[1]);
		free_tab(cmd_split);
		g_glob->exit_ret = 1;
		return (true);
	}
	closedir(dir);
	ft_chdir(cmd_split[1], 16);
	return (false);
}

bool	cd_parent(void)
{
	char	**cmd_split;

	if (ft_lstsize(*g_glob->cmds) == 1)
	{
		cmd_split = ft_split_sep(((t_cmd *)(*g_glob->cmds)->content)->str, \
			" \t");
		if (cmd_split[0] && !ft_strncmp(cmd_split[0], "cd", 3))
		{
			if (cmd_split[1])
			{
				if (cd_parent_arg(cmd_split))
					return (true);
			}
			else
				ft_chdir(get_env_node("HOME")->content + 5, 16);
			free_tab(cmd_split);
			g_glob->exit_ret = 0;
			return (true);
		}
		free_tab(cmd_split);
	}
	return (false);
}
