/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nuke.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:25:14 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/06 15:48:58 by zhabri           ###   ########.fr       */
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
}
