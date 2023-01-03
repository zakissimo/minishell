/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:40:50 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/03 13:25:40 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env_node(char *var)
{
	t_list	*envp_entry;

	envp_entry = *g_glob->envp;
	while (ft_strncmp((char *)envp_entry->content, var, ft_strlen(var)))
		envp_entry = envp_entry->next;
	return (envp_entry);
}

void	ft_chdir(char *dir, int size)
{
	char	*ret;
	char	*tmp;
	t_list	*pwd;
	t_list	*old_pwd;

	pwd = get_env_node("PWD=");
	old_pwd = get_env_node("OLDPWD=");
	ret = NULL;
	free_null(old_pwd->content);
	tmp = ft_strdup(pwd->content + 4);
	old_pwd->content = ft_strjoin("OLDPWD=", tmp);
	free_null(tmp);
	tmp = NULL;
	chdir(dir);
	while (ret == NULL)
	{
		size *= 2;
		free_null(tmp);
		while (tmp == NULL)
			tmp = ft_calloc(size, sizeof(char));
		ret = getcwd(tmp, size);
	}
	free_null(pwd->content);
	pwd->content = ft_strjoin("PWD=", tmp);
	free_null(tmp);
}

void	cd(char *cmd)
{
	char	**cmd_split;
	DIR		*dir;

	cmd_split = ft_split_sep(cmd, " \t");
	if (cmd_split[1])
	{
		if (cmd_split[2])
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			g_glob->exit_ret = 1;
			free_tab(cmd_split);
			return ;
		}
		dir = opendir(cmd_split[1]);
		if (!dir)
		{
			perror("minishell: ");
			free_tab(cmd_split);
			return ;
		}
		ft_chdir(cmd_split[1], 16);
		return ;
	}
	ft_chdir(get_env_node("HOME=")->content + 5, 16);
	free_tab(cmd_split);
}
