/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:54:10 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/13 14:12:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ft_chdir(t_list **pwd, t_list **old_pwd)
{
	*pwd = get_env_node("PWD");
	*old_pwd = get_env_node("OLDPWD");
}

void	free_and_null(char **tmp)
{
	free_null(*tmp);
	*tmp = NULL;
}

void	print_error_dir_cd(char *dir)
{
	char	*err;

	err = ft_strjoin("minishell: cd: ", dir);
	perror(err);
	free(err);
}

char	*get_home_content(void)
{
	t_list	*env_node;

	env_node = get_env_node("HOME");
	if (env_node == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (env_node->content + 5);
}

void	ft_chdir_core(int size, char **tmp, t_list *pwd)
{
	char	*ret;

	ret = NULL;
	while (ret == NULL)
	{
		size *= 2;
		free_and_null(tmp);
		while (*tmp == NULL)
			*tmp = ft_calloc(size, sizeof(char));
		ret = getcwd(*tmp, size);
	}
	if (pwd)
	{
		free_null(pwd->content);
		pwd->content = ft_strjoin("PWD=", *tmp);
	}
	else
		ft_lstadd_back(g_glob->envp, ft_lstnew(ft_strjoin("PWD=", *tmp)));
	free_null(*tmp);
}
