/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:06:54 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/19 14:54:17 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

bool	ft_open_in(t_cmd *node, t_token *token)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	if (token->label == INFILE)
		node->fd_in = open(token->arg, O_RDONLY);
	else
		node->fd_in = open(token->arg, O_RDONLY);
	if (node->fd_in == -1)
	{
		perror(token->arg);
		return (true);
	}
	return (false);
}

bool	ft_open_out(t_cmd *node, t_token *token)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	if (token->label == OUTFILE)
		node->fd_out = open(token->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		node->fd_out = open(token->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		perror(token->arg);
		return (true);
	}
	return (false);
}
