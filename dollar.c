/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:15 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/09 11:25:54 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	infile_exception(t_token *var)
{
	int					i;
	char				*second_part;
	char				*tmp;
	char				**arg_split;

	arg_split = ft_split_quotes_keep_sep(var->arg, "<>|");
	second_part = ft_calloc(1, sizeof(char));
	if (arg_split[1])
	{
		i = 1;
		while (arg_split[i])
		{
			tmp = ft_strjoin("\"", arg_split[i]);
			tmp = ft_strjoinf(tmp, "\"");
			second_part = ft_strjoinf(second_part, tmp);
			free(tmp);
			i++;
		}
	}
	free(var->arg);
	var->arg = ft_strjoin(arg_split[0], second_part);
	free(second_part);
	free_tab(arg_split);
}

static void	expand_bis(t_list *curr, t_token *var, char *env, char *tmp)
{
	if (tmp[0] != '?')
	{
		if (curr && env)
		{
			var->arg = ft_strdup(ft_strchr(env, '=') + 1);
			infile_exception(var);
		}	
		else
		{
			if (ft_strlen(tmp) == 1)
				var->arg = ft_strdup("$");
			else
				var->arg = ft_strdup("");
		}
	}
	else
		var->arg = ft_strjoinf(ft_itoa(g_glob->exit_ret), \
			var->not_expanded + 1);
	free(tmp);
}

void	expand(t_token *var)
{
	char	*tmp;
	char	*env;
	t_list	*curr;

	tmp = ft_strjoin(var->arg, "=");
	var->not_expanded = ft_strdup(var->arg);
	curr = *g_glob->envp;
	env = (char *)curr->content;
	while (curr && ft_strncmp(env, tmp, ft_strlen(tmp)))
	{
		curr = curr->next;
		if (curr)
			env = (char *)curr->content;
	}
	free(var->arg);
	expand_bis(curr, var, env, tmp);
}

static bool	str_is_op(char *needle)
{
	int						i;
	static const char		*op_tab[13] = {"<<", ">>", "|", \
		">", "<", " ", "$", "\"", "'", "/", "\t", NULL};

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
