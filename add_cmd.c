/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:30:28 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/10 12:52:58 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd(t_token *token, t_list **cmds, bool *pb)
{
	t_cmd	*node;

	node = NULL;
	if (*pb)
	{
		node = ((t_cmd *)ft_lstlast(*cmds)->content);
		if (node->str)
			free(node->str);
		if (node->fd_in > 2)
			close(node->fd_in);
		if (node->fd_out > 2)
			close(node->fd_out);
		node->str = ft_strdup(token->arg);
		node->fd_in = -3;
		node->fd_out = 1;
	}
	else
	{
		node = init_cmd_token(-3, 1, ft_strdup(token->arg), false);
		if (((t_cmd *)ft_lstlast(*cmds)->content)->fd_out == 1)
			((t_cmd *)ft_lstlast(*cmds)->content)->fd_out = -3;
		ft_lstadd_back(cmds, ft_lstnew(node));
	}
	*pb = false;
}
