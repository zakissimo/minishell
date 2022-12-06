/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:11:50 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/06 14:22:10 by zhabri           ###   ########.fr       */
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

int	op_error(const char *input)
{
	size_t				i;
	size_t				j;
	char				*trimmed;
	static const char	*op_tab[6] = {"<<", ">>", "|", ">", "<", NULL};

	i = 0;
	trimmed = ft_strtrim((char *)input, " \t");
	j = ft_strlen(trimmed);
	while (op_tab[i])
	{
		j -= ft_strlen(op_tab[i]);
		if (!strncmp(trimmed + j, op_tab[i], ft_strlen(op_tab[i])))
		{
			ft_putstr_fd("Parse error\n", 2);
			return (-1);
		}
		j += ft_strlen(op_tab[i]);
		i++;
	}
	free(trimmed);
	return (0);
}
