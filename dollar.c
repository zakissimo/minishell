/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:15 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/26 15:43:01 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

void	expand(t_token *var)
{
	char	*tmp;
	char	*env;
	t_list	*curr;

	tmp = ft_strjoin(var->arg, "=");
	var->not_expanded = ft_strdup(var->arg);
	curr = *g_glob->envp;
	env = (char *)curr->content;
	while (curr && \
		ft_strncmp(env, tmp, ft_strlen(tmp)))
	{
		curr = curr->next;
		if (curr)
			env = (char *)curr->content;
	}
	if (var->arg[0] != '?')
	{
		free(tmp);
		free(var->arg);
		if (curr && env)
			var->arg = ft_strdup(ft_strchr(env, '=') + 1);
		else
			var->arg = ft_strdup("");
	}
	else
		var->arg = ft_strjoinf(ft_itoa(g_glob->exit_ret), \
			var->not_expanded + 1);
}

static bool	str_is_op(char *needle)
{
	int						i;
	static const char		*op_tab[11] = {"<<", ">>", "|", \
		">", "<", "$", " ", "\"", "'", "/", NULL};

	i = 0;
	while (op_tab[i])
	{
		if (!strncmp(op_tab[i], needle, ft_strlen(op_tab[i])))
			return (true);
		i++;
	}
	return (false);
}

void	find_var(t_token *token, char *input)
{
	int						i;
	size_t					len;

	len = 0;
	if (token)
	{
		i = token->str_idx + 1;
		if (input[i] == '?')
			token->arg = ft_strdup("?");
		else
		{
			while (input[i] && !str_is_op(input + i))
			{
				i++;
				len++;
			}
			token->arg = ft_substr(input, token->str_idx + 1, len);
		}
	}
}
