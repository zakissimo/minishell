/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brenaudo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:26:02 by brenaudo          #+#    #+#             */
/*   Updated: 2023/01/04 16:26:18 by brenaudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_cmp_sort(char *s1, char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else if (*s1 < *s2)
		return (-1);
	else
		return (1);
}

void	sort_ascii(char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[j + 1])
		{
			if (str_cmp_sort(envp[j], envp[j + 1]) == 1)
			{
				tmp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	**cut_on_first(char *str, char sep)
{
	int		i;
	char	**ret;

	ret = NULL;
	while (ret == NULL)
		ret = ft_calloc(3, sizeof(char *));
	ret[2] = NULL;
	i = 0;
	while (str && str[i] && str[i] != sep)
		i++;
	ret[0] = ft_substr(str, 0, i);
	ret[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (ret);
}

char	*longest_str(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
		i++;
	while (s2 && s2[j])
		j++;
	if (i > j)
		return (s1);
	else
		return (s2);
}
