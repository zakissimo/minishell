/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:30:28 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/20 10:59:41 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
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
		node->str = ft_strdup(token->arg);
		node->fd_in = 0;
		node->fd_out = 1;
	}
	else
	{
		node = init_cmd_token(0, 1, ft_strdup(token->arg));
		ft_lstadd_back(cmds, ft_lstnew(node));
	}
	*pb = false;
}
