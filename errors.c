/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:11:50 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/19 11:00:13 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static int	find_next_quote(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	return (i + 1);
}

int	quote_error(const char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
			i += find_next_quote(input + i + 1, input[i]);
		if (i >= ft_strlen(input))
		{
			ft_putstr_fd("Parse error (quote)\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

char	*op_error_trimmed(t_list *curr)
{
	t_token	*token;
	char	*trimmed;
	t_token	*token_next;

	while (curr->next && ((t_token *)curr->next->content)->label == VARIABLE)
		curr = curr->next;
	token_next = NULL;
	token = (t_token *)curr->content;
	if (curr->next)
	{
		token_next = (t_token *)curr->next->content;
		trimmed = ft_strtrimf(ft_substr(g_glob->input, token->str_idx \
			+ ft_strlen(token->str), \
			token_next->str_idx - \
			(ft_strlen(token->str) + token->str_idx)), " \t");
	}
	else
		trimmed = ft_strtrimf(ft_substr(g_glob->input, token->str_idx \
			+ ft_strlen(token->str), \
			ft_strlen(g_glob->input) - token->str_idx), " \t");
	return (trimmed);
}

int	op_error(void)
{
	t_list	*curr;
	char	*trimmed;

	curr = NULL;
	if (g_glob->head)
		curr = *g_glob->head;
	while (curr)
	{
		trimmed = op_error_trimmed(curr);
		if (((t_token *)curr->content)->label != VARIABLE \
			&& ((t_token *)curr->content)->label != PIPE)
		{
			if (!ft_strlen(trimmed))
			{
				ft_putstr_fd("Parse error\n", 2);
				free(trimmed);
				return (-1);
			}
			free(trimmed);
		}
		curr = curr->next;
	}
	return (0);
}
