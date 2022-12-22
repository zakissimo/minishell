/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis_bis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 09:51:21 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/22 14:05:03 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static bool	str_is_op(char *needle)
{
	int						i;
	static const char		*op_tab[6] = {"<<", ">>", "|", \
		">", "<", NULL};

	i = 0;
	while (op_tab[i])
	{
		if (!strncmp(op_tab[i], needle, ft_strlen(op_tab[i])))
			return (true);
		i++;
	}
	return (false);
}

char	*get_first(void)
{
	int		i;
	char	*trimmed;
	char	*ret;

	i = 0;
	trimmed = ft_strtrim(g_glob->input, " \t");
	if (trimmed && trimmed[0])
	{
		while (trimmed[i] && !str_is_op(trimmed + i))
			i++;
		ret = ft_substr(trimmed, 0, i);
		free(trimmed);
		return (ret);
	}
	return (NULL);
}

void	eof_limiter_not_found(char *here_doc_entry, char *limiter)
{
	if (here_doc_entry == NULL)
	{
		printf("minishell: warning: here-document");
		printf(" delimited by end-of-file (wanted '%s')\n", limiter);
	}
	free(here_doc_entry);
	free(limiter);
}
