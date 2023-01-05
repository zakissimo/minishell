/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_after.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 10:02:48 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/05 15:09:13 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_node(t_list *curr, t_label op, bool next)
{
	t_token	*token;

	if (curr && next)
		curr = curr->next;
	while (curr)
	{
		token = (t_token *)curr->content;
		if (token->label == op)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	get_new_len(void)
{
	int		new_len;
	t_list	*curr;
	t_token	*token;

	new_len = ft_strlen(g_glob->input);
	curr = *g_glob->head;
	while (curr)
	{
		token = (t_token *)curr->content;
		if (token->label == VARIABLE)
		{
			new_len -= ft_strlen(token->not_expanded) + 1;
			new_len += ft_strlen(token->arg);
		}
		curr = curr->next;
	}
	return (new_len);
}

void	get_after_loop(char *expanded_input, t_list *curr, int i, int j)
{
	if (curr)
	{
		while (g_glob->input[i])
		{
			if (curr && i > ((t_token *)(curr->content))->str_idx)
				curr = get_node(curr, VARIABLE, true);
			if (curr && i == ((t_token *)(curr->content))->str_idx)
			{
				ft_strlcat(expanded_input, \
					((t_token *)(curr->content))->arg, get_new_len() + 1);
				j += ft_strlen(((t_token *)(curr->content))->arg);
				i += ft_strlen(((t_token *)(curr->content))->not_expanded) + 1;
			}
			else
				expanded_input[j++] = g_glob->input[i++];
		}
		free(g_glob->input);
		g_glob->input = expanded_input;
	}
	else
		free(expanded_input);
}

static void	heredoc_dollar_exception(void)
{
	char	*arg;
	t_list	*curr;

	curr = *g_glob->head;
	if (curr)
	{
		while (curr->next)
		{
			if (((t_token *)(curr->content))->label == HEREDOC \
				&& ((t_token *)(curr->next->content))->label == VARIABLE)
			{
				free(((t_token *)(curr->next->content))->arg);
				arg = ft_strjoin("\'$", \
					((t_token *)(curr->next->content))->not_expanded);
				arg = ft_strjoinf(arg, "\'");
				((t_token *)(curr->next->content))->arg = arg;
			}
			curr = curr->next;
		}
	}
}

void	get_after_op(void)
{
	int		i;
	int		j;
	t_list	*curr;
	char	*expanded_input;

	expanded_input = ft_calloc((get_new_len() + 1), sizeof(char));
	i = 0;
	j = 0;
	curr = *g_glob->head;
	curr = get_node(curr, VARIABLE, false);
	heredoc_dollar_exception();
	get_after_loop(expanded_input, curr, i, j);
}
