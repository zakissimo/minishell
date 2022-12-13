/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nuke.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:25:14 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/13 14:22:49 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_str(void *n)
{
	t_token	*node;

	node = (t_token *)n;
	free((char *)node->str);
	if (node->arg)
		free((char *)node->arg);
	if (node->not_expanded)
		free((char *)node->not_expanded);
}

void	free_op_list(void)
{
	ft_lstiter(*g_glob->head, free_token_str);
	ft_lstclear(g_glob->head, free);
}

void	clear_cmds(void)
{
	int		i;
	t_list	*cmd;
	t_list	*next;

	if (g_glob->cmds)
	{
		cmd = *g_glob->cmds;
		while (cmd)
		{
			i = 0;
			while (((char **)cmd->content)[i])
			{
				free(((char **)cmd->content)[i]);
				i++;
			}
			free(((char **)cmd->content));
			next = cmd->next;
			free(cmd);
			cmd = next;
		}
	}
}

void	nuke_glob(void)
{
	free(g_glob->input);
	free(g_glob->head);
}
