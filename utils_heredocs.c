/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:47:46 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/29 13:48:51 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*name_generator(void)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = NULL;
	while (file_name == NULL)
		file_name = malloc(10 * sizeof(char));
	file_name[0] = '.';
	file_name[9] = '\0';
	while (++i < 9)
		file_name[i] = 'a';
	while (file_name == NULL || access(file_name, 0) == 0)
	{
		file_name[8]++;
		i = 9;
		while (--i > 1)
		{
			if (file_name[i] == 'z' + 1)
			{
				file_name[i - 1]++;
				file_name[i] = 'a';
			}
		}
	}
	return (file_name);
}

char	*get_limiter(t_token *token)
{
	int		i;
	char	*limiter;

	i = 0;
	while (ft_isprint_nospace(token->arg[i]))
	{
		if (token->arg[i] == '"')
			i += find_quote(token->arg + i + 1, '"');
		else if (token->arg[i] == '\'')
			i += find_quote(token->arg + i + 1, '\'');
		i++;
	}
	limiter = ft_substr(token->arg, 0, i);
	return (remove_quotes(limiter));
}
