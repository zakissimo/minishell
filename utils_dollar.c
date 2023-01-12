/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:26:56 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/12 14:28:25 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	infile_exception_tmp(char **second_part, char *arg_split)
{
	char	*tmp;

	tmp = ft_strjoinf(ft_strjoin("\"", arg_split), "\"");
	*second_part = ft_strjoinf(*second_part, tmp);
	free(tmp);
}
