/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:16:11 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/02 11:16:27 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void	pwd(void)
{
	int		size;
	char	*path;
	char	*ret;
	
	size = 16;
	path = NULL;
	ret = NULL;
	while (ret == NULL)
	{
		size *= 2;
		free(path);
		path = NULL;
		while (path == NULL)
			path = ft_calloc(size, sizeof(char));
		ret = getcwd(path, size);
	}
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
}
