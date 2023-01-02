/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:56:08 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/30 12:40:23 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

bool	str_is_numeric(char *str)
{
	int	i;

	i = 0;
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

bool	exit_parent(void)
{
	t_cmd	*cmd;
	char	**cmd_split;

	if (ft_lstsize(g_glob->cmds) == 1)
	{
		cmd = ((t_cmd *)(*g_glob->cmds)->content);
		cmd_split = ft_split(cmd->str, ' ');
		if (!ft_strncmp(cmd_split[0], "exit", 5))
		//	TODO if cmd_split[1] exists it needs to be:
		//		1- numeric
		//		2- lower than LLMAX higer than LLMIN
		//		cmd_split[2] is NULL
		//		Always print exit in stderr
		//		Always change g_glob->ret according to the following:
		//			1- If the numeric argument is OK change to it
		//			2- If its not numeric change to 2 print error and exit
		//			3- Change to 1 if too many print error dont exit
	}
}
// TODO: IF IN CHILD never exit but change g_glob->ret
