/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:24:58 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/03 11:40:06 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static bool	is_echo_with_newline(char *arg)
{
	int	i;

	if (arg && arg[0] != '-')
		return (true);
	i = 1;
	while (arg[i] == 'n')
		i++;
	if (!arg[i])
		return (false);
	return (true);
}

void	echo(char *cmd)
{
	int		i;
	char	**cmd_split;
	bool	newline;

	i = 1;
	cmd_split = ft_split_sep(cmd, " \t");
	newline = is_echo_with_newline(cmd_split[1]);
	if (!newline)
		i++;
	while (cmd_split[i])
		ft_putstr_fd(cmd_split[i++], 1);
	if (newline)
		ft_putchar_fd('\n', 1);
	free_tab(cmd_split);
}
