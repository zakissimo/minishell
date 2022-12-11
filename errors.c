/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:11:50 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/11 16:21:31 by zhabri           ###   ########.fr       */
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

int	op_error(void)
{
	char	*trimmed;
	t_token	*token;
	t_list	*curr;

	trimmed = ft_strtrim(g_glob->input, " \t");
	curr = NULL;
	if (g_glob->head)
		curr = *g_glob->head;
	if (curr)
	{
		token = (t_token *)ft_lstlast(curr)->content;
		if (token && token->label != VARIABLE
			&& ft_strlen(trimmed) == token->str_idx + ft_strlen(token->str))
		{
			ft_putstr_fd("Parse error\n", 2);
			free(trimmed);
			return (-1);
		}
	}
	free(trimmed);
	return (0);
}
