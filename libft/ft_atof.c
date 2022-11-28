/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 07:51:51 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/16 08:09:09 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_is_float(char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	return ((int)ft_strlen(str) == i && i < 41);
}

static int	dot_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	return (str[i] == '.');
}

static int	get_neg(char **str)
{
	int	i;
	int	neg;

	i = 0;
	neg = 1;
	if (*str[i] == '-' || *str[i] == '+')
	{
		if (*str[i] == '-')
			neg = -1;
		(*str)++;
	}
	return (neg);
}

float	ft_atof(char *str, void (*panic)(void))
{
	int		i;
	int		neg;
	double	ret;

	i = 0;
	ret = 0.0;
	neg = get_neg(&str);
	if (!str_is_float(str) || !dot_in_str(str))
		if (panic)
			(*panic)();
	while (str[i])
	{
		if (str[i] == '.')
			i++;
		ret *= 10.0;
		ret += str[i] - '0';
		i++;
	}
	while (str[i - 1] != '.')
	{
		ret /= 10.0;
		i--;
	}
	return ((float)(ret * neg));
}
