/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nuke.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:25:14 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/11 16:13:13 by zhabri           ###   ########.fr       */
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

void	nuke_glob(void)
{
	free(g_glob->input);
	free(g_glob->head);
}
