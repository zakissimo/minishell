/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:06:54 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/06 11:39:40 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_open_in(t_cmd *node, t_token *token)
{
	if (node->fd_in > 2)
		close(node->fd_in);
	if (token->file)
		node->fd_in = open(token->file, O_RDONLY);
	if (node->fd_in == -1 && token->label == INFILE)
	{
		g_glob->exit_ret = 1;
		perror(token->file);
		return (true);
	}
	else if (node->fd_in == -1 && token->label == HEREDOC)
	{
		g_glob->exit_ret = 1;
		ft_putstr_fd("Error on heredoc creation (feels bad man)\n", 2);
		return (true);
	}
	return (false);
}

bool	ft_open_out(t_cmd *node, t_token *token)
{
	if (node->fd_out > 2)
		close(node->fd_out);
	if (token->label == OUTFILE)
		node->fd_out = open(token->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		node->fd_out = open(token->file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (node->fd_out == -1)
	{
		g_glob->exit_ret = 1;
		perror(token->file);
		return (true);
	}
	return (false);
}
