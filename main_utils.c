/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:40:36 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/23 11:35:14 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	final_clean_up(void)
{
	ft_lstclear(g_glob->envp, free);
	free_null(g_glob->envp);
	free_null(g_glob);
	rl_clear_history();
}

void	free_null(void *var)
{
	if (var)
		free(var);
	var = NULL;
}
