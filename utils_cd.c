/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:54:10 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/04 13:54:14 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_null(char **tmp)
{
	free_null(*tmp);
	*tmp = NULL;
}

void	print_error_dir_cd(char *dir)
{
	char	*err;

	err = ft_strjoin("minishell: cd: ", dir);
	perror(err);
	free(err);
}
