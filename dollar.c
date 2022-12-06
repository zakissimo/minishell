/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:15 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/06 15:48:31 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_node(t_list *curr, char *op)
{
	t_token	*token;

	while (curr)
	{
		token = (t_token *)curr->content;
		if (!strncmp(token->str, op, get_longest_str((char *)token->str, op)))
			return (token);
		curr = curr->next;
	}
	return (NULL);
}

bool	str_is_op(char *needle)
{
	int						i;
	static const char		*op_tab[10] = {"<<", ">>", "|", \
		">", "<", "$", " ", "\"", "'", NULL};

	i = 0;
	while (op_tab[i])
	{
		if (!strncmp(op_tab[i], needle, ft_strlen(op_tab[i])))
			return (true);
		i++;
	}
	return (false);
}

void	find_var(t_token *token, char *input)
{
	int						i;
	size_t					len;

	len = 0;
	if (token)
	{
		i = token->str_idx + 1;
		while (input[i] && !str_is_op(input + i))
		{
			i++;
			len++;
		}
		token->arg = ft_substr(input, token->str_idx + 1, len);
	}
}
