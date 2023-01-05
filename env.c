/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:48:10 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/05 10:48:12 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_no_arg(int fd_out)
{
	int		i;
	char	**envp;

	envp = envp_list_to_tab();
	i = 0;
	while (envp[i])
	{
        if (ft_strncmp(envp[i], "_=", 2))
        {
            ft_putstr_fd(envp[i], fd_out);
	        ft_putchar_fd('\n', fd_out);
        }
		i++;
	}
    free_tab(envp);
}

void	env(char *cmd, int fd_out)
{
    (void)cmd;
	env_no_arg(fd_out);
	close(fd_out);
	clean_exit(NULL);
	exit(0);
}
