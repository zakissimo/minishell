/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 11:31:23 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/03 11:51:39 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *name)
{
	t_list	*env_cpy;

	env_cpy = *g_glob->envp;
	while (env_cpy && env_cpy->next && \
		&& ft_strncmp(env_cpy->next->content, name, ft_strlen(name) + 1) != 0)
		env_cpy = env_cpy->next;
	//cas particulier si un seul
}
