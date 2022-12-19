/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:14:40 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/19 09:42:22 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"
#include <stdlib.h>

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

void	find_cmd(t_list **cmds)
{
	char	*trimmed;
	int		i;

	i = 0;
	trimmed = ft_strtrim(g_glob->input, " \t");
	if (trimmed && trimmed[i] && trimmed[0] != '<')
	{
		while (trimmed[i] && !str_is_op(trimmed + i))
			i += skip_if_quotes(trimmed, i);
		ft_lstadd_back(cmds, ft_lstnew(ft_substr(trimmed, 0, i)));
	}
	free(trimmed);
}

void	find_cmd_infile(t_token *token, t_list **cmds)
{
	int		i;
	char	*cmd;
	char	*file;

	i = 0;
	while (ft_isprint_nospace(token->arg[i]))
	{
		if (token->arg[i] == '"')
			i += find_quote(token->arg + i + 1, '"');
		else if (token->arg[i] == '\'')
			i += find_quote(token->arg + i + 1, '\'');
		i++;
	}
	file = ft_substr(token->arg, 0, i);
	cmd = ft_strtrimf(ft_strdup(token->arg + i), " \t");
	ft_lstadd_back(cmds, ft_lstnew(cmd));
	free(token->arg);
	token->arg = remove_quotes(file);
}
void	find_cmd_outfile(t_token *token, t_list **cmds)
{
	int		i;
	char	*cmd;
	char	*file;
	char	*cmd_rest;

	i = 0;
	while (ft_isprint_nospace(token->arg[i]))
	{
		if (token->arg[i] == '"')
			i += find_quote(token->arg + i + 1, '"');
		else if (token->arg[i] == '\'')
			i += find_quote(token->arg + i + 1, '\'');
		i++;
	}
	file = ft_substr(token->arg, 0, i);
	cmd_rest = ft_strtrimf(ft_strdup(token->arg + i), " \t");
	cmd = ft_lstlast(*cmds)->content;
	ft_lstlast(*cmds)->content = ft_strjoinf(ft_strjoinf(cmd, " "), cmd_rest);
	free(cmd_rest);
	free(token->arg);
	token->arg = remove_quotes(file);
}

void	get_cmd(void)
{
	t_list	*curr;
	t_token	*token;
	t_list	**cmds;

	curr = *g_glob->head;
	cmds = malloc(sizeof(t_list *));
	*cmds = NULL;
	find_cmd(cmds);
	while (curr)
	{
		token = (t_token *)curr->content;
		if (token->label == INFILE || token->label == HEREDOC)
			find_cmd_infile(token, cmds);
		else if (token->label == OUTFILE || token->label == OUTFILE_A)
			find_cmd_outfile(token, cmds);
		else if (token->label == PIPE && token->arg[0] != '\0')
			ft_lstadd_back(cmds, ft_lstnew(ft_strdup(token->arg)));
		curr = curr->next;
	}
	g_glob->cmds = cmds;
}
