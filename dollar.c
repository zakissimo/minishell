/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:15 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/08 11:27:58 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	expand(t_token *var)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var->arg, "=");
	var->not_expanded = ft_strdup(var->arg);
	while (g_glob->envp[i] && \
		ft_strncmp(g_glob->envp[i], tmp, ft_strlen(tmp)))
		i++;
	if (var->arg[0] != '?')
	{
		free(tmp);
		free(var->arg);
		if (g_glob->envp[i])
			var->arg = ft_strdup(ft_strchr(g_glob->envp[i], '=') + 1);
		else
			var->arg = ft_strdup("");
	}
}

t_list	*get_node(t_list *curr, t_label op, bool next)
{
	t_token	*token;

	if (curr && next)
		curr = curr->next;
	while (curr)
	{
		token = (t_token *)curr->content;
		if (token->label == op)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

bool	str_is_op(char *needle)
{
	int						i;
	static const char		*op_tab[10] = {"<<", ">>", "|", \
		">", "<", "$", " ", "\"", "'", NULL};

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

int	get_new_len(void)
{
	int		new_len;
	t_list	*curr;
	t_token	*token;

	new_len = ft_strlen(g_glob->input);
	curr = *g_glob->head;
	while (curr)
	{
		token = (t_token *)curr->content;
		if (token->label == VARIABLE)
		{
			new_len -= ft_strlen(token->not_expanded) + 1;
			new_len += ft_strlen(token->arg);
		}
		curr = curr->next;
	}
	return (new_len);
}

void	expand_input(void)
{
	int		i;
	int		j;
	t_list	*curr;
	t_token	*token;
	char	*expanded_input;

	expanded_input = malloc((get_new_len() + 1) * sizeof(char));
	i = 0;
	j = 0;
	curr = *g_glob->head;
	curr = get_node(curr, VARIABLE, false);
	if (curr)
	{
		token = (t_token *)curr->content;
		while (g_glob->input[i])
		{
			if (i > token->str_idx)
			{
				curr = get_node(curr, VARIABLE, true);
				if (curr)
					token = (t_token *)curr->content;
			}
			if (curr && i == token->str_idx)
			{
				expanded_input = ft_strjoinf(expanded_input, token->arg);
				j += ft_strlen(token->arg);
				i += ft_strlen(token->not_expanded) + 1;
			}
			else
				expanded_input[j++] = g_glob->input[i++];
		}
		g_glob->input = expanded_input;
		printf("%s\n", g_glob->input);
	}
}
