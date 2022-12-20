/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nuke.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:25:14 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/20 09:14:08 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

void	free_token_str(void *n)
{
	t_token	*node;

	node = (t_token *)n;
	if (node->str)
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
	t_list	*cmd;
	t_list	*next;

	if (g_glob->cmds)
	{
		cmd = *g_glob->cmds;
		while (cmd)
		{
			if (cmd->content)
			{
				if (((t_cmd *)cmd->content)->str)
					free(((t_cmd *)cmd->content)->str);
				if (((t_cmd *)cmd->content)->fd_in > 2)
					close(((t_cmd *)cmd->content)->fd_in);
				if (((t_cmd *)cmd->content)->fd_out > 2)
					close(((t_cmd *)cmd->content)->fd_out);
				free(cmd->content);
			}
			next = cmd->next;
			free(cmd);
			cmd = next;
		}
	}
}

void	clear_cmd(void *curr)
{
	t_cmd	*cmd;

	if (curr)
	{
		cmd = ((t_cmd *)curr);
		if (cmd->str)
			free(cmd->str);
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		free(cmd);
	}
}

void	lst_dellast(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*prev;
	t_list	*n;

	if (lst && (*lst) && del)
	{
		curr = *lst;
		prev = *lst;
		n = (*lst)->next;
		while (n)
		{
			prev = curr;
			curr = n;
			n = n->next;
		}
		ft_lstdelone(curr, del);
		prev->next = NULL;
	}
}
