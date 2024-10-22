/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:04:06 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/09 11:23:44 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_args(void)
{
	int		idx;
	t_list	*curr;
	t_list	*next;
	t_token	*token;

	curr = *g_glob->head;
	while (curr)
	{
		token = (t_token *)curr->content;
		next = curr->next;
		if (next)
			idx = ((t_token *)next->content)->str_idx;
		else
			idx = ft_strlen(g_glob->input);
		if (token->label != VARIABLE)
		{
			token->arg = ft_substr(g_glob->input, \
				token->str_idx + ft_strlen(token->str), \
				idx - token->str_idx - ft_strlen(token->str));
			token->arg = ft_strtrimf(token->arg, " \t");
		}
		curr = curr->next;
	}
}
