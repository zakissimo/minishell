/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 07:49:48 by zhabri            #+#    #+#             */
/*   Updated: 2022/10/01 11:05:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*n;

	if (lst && (*lst) && del)
	{
		curr = *lst;
		n = (*lst)->next;
		while (n)
		{
			ft_lstdelone(curr, del);
			curr = n;
			n = n->next;
		}
		ft_lstdelone(curr, del);
		(*lst) = NULL;
	}
}
