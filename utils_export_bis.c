/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:38:28 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/06 10:48:30 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	plus_end_str(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i + 1])
		i++;
	if (str && str[i] == '+')
		return (true);
	return (false);
}

void	free_and_set_exit_ret(char **var_split, int ret)
{
	free_tab(var_split);
	g_glob->exit_ret = ret;
}

void	init_new_var(bool plus_char, char *var, char **var_split)
{
	if (!plus_char)
		ft_lstadd_back(g_glob->envp, ft_lstnew(ft_strdup(var)));
	else
		ft_lstadd_back(g_glob->envp, \
			ft_lstnew(ft_strdup(ft_strjoin(var_split[0], \
			var_split[1]))));
}

void	edit_var(bool plus_char, char *var, char **var_split, t_list *env_cpy)
{
	if (!plus_char)
	{
		free(env_cpy->content);
		env_cpy->content = ft_strdup(var);
	}
	else
	{
		if (ft_strchr(env_cpy->content, '='))
			env_cpy->content = ft_strjoinf(env_cpy->content, \
				var_split[1] + 1);
		else
			env_cpy->content = ft_strjoinf(env_cpy->content, \
				var_split[1]);
	}
}
