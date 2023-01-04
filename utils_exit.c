/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:16:30 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/02 14:26:51 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	str_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

bool	overflows_llong(char *str)
{
	bool	is_neg;
	int		len;

	is_neg = false;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			is_neg = true;
		str++;
	}
	len = ft_strlen(str);
	if (len > 19)
		return (true);
	else if (len < 19)
		return (false);
	if (!is_neg && ft_strncmp(str, "9223372036854775807", 19) > 0)
		return (true);
	if (is_neg && ft_strncmp(str, "9223372036854775808", 19) > 0)
		return (true);
	return (false);
}

bool	is_valid_exit_arg(char *cmd)
{
	return (!((!str_is_numeric(cmd) \
		|| (str_is_numeric(cmd) && overflows_llong(cmd)))));
}

void	print_exit_num_error(char *cmd)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

bool	check_exit_error(char **cmd_split)
{
	if (!is_valid_exit_arg(cmd_split[1]))
		print_exit_num_error(cmd_split[1]);
	else if (cmd_split[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_glob->exit_ret = 1;
		return (true);
	}
	return (false);
}
