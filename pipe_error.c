/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:02:03 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/22 10:46:25 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_error_loop(t_list *curr, t_list *prev, char *trimmed)
{
	prev = curr;
	trimmed = op_error_trimmed(prev);
	while (curr->next)
	{
		curr = curr->next;
		if (((t_token *)prev->content)->label == PIPE \
			&& ((t_token *)curr->content)->label == PIPE \
			&& !ft_strlen(trimmed))
		{
			ft_putstr_fd("Pipe error\n", 2);
			free(trimmed);
			return (-1);
		}
		free(trimmed);
		trimmed = op_error_trimmed(curr);
		if (((t_token *)curr->content)->label == PIPE \
			&& curr->next == NULL && !ft_strlen(trimmed))
		{
			ft_putstr_fd("Pipe error\n", 2);
			free(trimmed);
			return (-1);
		}
	}
	free(trimmed);
	return (0);
}

int	pipe_error_bis(char *trimmed, char *op_pipe, t_list *curr)
{
	t_token	*token;

	token = NULL;
	if (curr->next)
		token = ((t_token *)curr->next->content);
	if (!ft_strlen(trimmed)
		|| (!ft_strlen(op_pipe) && !token)
		|| (!ft_strlen(op_pipe) && token && token->label == PIPE))
	{
		free(op_pipe);
		free(trimmed);
		ft_putstr_fd("Pipe error\n", 2);
		return (-1);
	}
	free(trimmed);
	free(op_pipe);
	return (0);
}

int	pipe_error(void)
{
	t_list	*curr;
	t_list	*prev;
	char	*trimmed;
	char	*op_pipe;

	curr = NULL;
	prev = NULL;
	trimmed = NULL;
	if (g_glob->head)
		curr = *g_glob->head;
	if (curr && curr->content && ((t_token *)curr->content)->label == PIPE)
	{
		trimmed = get_first();
		op_pipe = ft_strtrim(((t_token *)curr->content)->arg, " \t");
		if (pipe_error_bis(trimmed, op_pipe, curr) == -1)
			return (-1);
	}
	if (curr)
		return (pipe_error_loop(curr, prev, trimmed));
	return (0);
}
