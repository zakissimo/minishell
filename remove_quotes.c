/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:43:05 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/18 10:43:08 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '"')
			i += find_quote(str + i + 1, '"');
		if (str[i] == '\'')
			i += find_quote(str + i + 1, '\'');
		if (str[i] == '"' || str[i] == '\'')
			count += 2;
		i++;
	}
	return (count);
}

static int	count_quotes_type(char *str, char quote_type)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] == quote_type)
			count++;
		i++;
	}
	return (count);
}

static bool	is_closing_quote(char *str, int i_init, char quote_type)
{
	int	i;

	i = i_init + 1;
	while (str && str[i] && str[i] != quote_type)
		i++;
	if (str && str[i] == quote_type)
		return (true);
	if (str && !str[i] && count_quotes_type(str, quote_type) % 2 == 0)
		return (true);
	return (false);
}

static void	init_remove_quotes(int *i, int *j, int *double_q, int *single_q)
{
	*double_q = 0;
	*single_q = 0;
	*i = 0;
	*j = 0;
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*ret;
	int		double_q;
	int		single_q;

	ret = ft_calloc(((ft_strlen(str) - count_quotes(str) + 1)), sizeof(char));
	init_remove_quotes(&i, &j, &double_q, &single_q);
	while (str[i])
	{
		if (str[i] == '"' && !single_q && is_closing_quote(str, i, '\"'))
			double_q = !double_q;
		else if (str[i] == '\'' && !double_q && is_closing_quote(str, i, '\''))
			single_q = !single_q;
		else if ((str[i] == '"' && single_q) || (str[i] == '\'' && double_q)
			|| (str[i] == '"' && !is_closing_quote(str, i, '\"'))
			|| (str[i] == '\'' && !is_closing_quote(str, i, '\''))
			|| (str[i] != '"' && str[i] != '\''))
			ret[j++] = str[i];
		i++;
	}
	free(str);
	return (ret);
}
