/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:53:15 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/13 13:57:10 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	trim_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		tab[i] = ft_strtrimf(tab[i], " \t");
		i++;
	}
}

void	split_cmds(void)
{
	t_list	*cmd;

	if (g_glob->cmds)
	{
		cmd = *g_glob->cmds;
		while (cmd)
		{
			cmd->content = ft_split_quotes(cmd->content, " \t");
			trim_tab(cmd->content);
			cmd = cmd->next;
		}
	}
}
