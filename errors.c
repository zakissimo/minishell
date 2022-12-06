/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:11:50 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/06 11:59:38 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_error(const char *input, char quote)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == quote)
		{
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
			{
				ft_putstr_fd("Parse Error (Quote)\n", 2);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
