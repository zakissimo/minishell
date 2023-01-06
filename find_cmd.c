/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:14:40 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/06 10:58:59 by zhabri           ###   ########.fr       */
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
	t_cmd	*node;
	int		i;

	i = 0;
	trimmed = ft_strtrim(g_glob->input, " \t");
	node = init_cmd_token(0, 1, NULL, true);
	if (trimmed && trimmed[0])
	{
		while (trimmed[i] && !str_is_op(trimmed + i))
			i += skip_if_quotes(trimmed, i);
		node->str = ft_substr(trimmed, 0, i);
	}
	ft_lstadd_back(cmds, ft_lstnew(node));
	free(trimmed);
}

void	find_cmd_infile(t_token *token, t_cmd *node, bool *pb)
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
	node->str = ft_strtrimf(ft_strjoinf(ft_strjoinf(node->str, " "), cmd), \
				" \t");
	free(cmd);
	if (token->label != HEREDOC)
		token->file = remove_quotes(file);
	else
		free(file);
	if (!g_glob->sig_int)
		*pb = ft_open_in(node, token);
	else
		*pb = false;
}

void	find_cmd_outfile(t_token *token, t_cmd *node, bool *pb)
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
	node->str = ft_strtrimf(ft_strjoinf(ft_strjoinf(node->str, " "), cmd), \
				" \t");
	free(cmd);
	token->file = remove_quotes(file);
	if (!g_glob->sig_int)
		*pb = ft_open_out(node, token);
	else
		*pb = false;
}

void	get_cmd(void)
{
	t_list	*curr;
	t_token	*token;
	t_list	**cmds;
	bool	pb;

	pb = false;
	curr = *g_glob->head;
	cmds = malloc(sizeof(t_list *));
	*cmds = NULL;
	find_cmd(cmds);
	while (curr)
	{
		token = (t_token *)curr->content;
		if (!pb && (token->label == INFILE || token->label == HEREDOC))
			find_cmd_infile(token, ft_lstlast(*cmds)->content, &pb);
		else if (!pb && (token->label == OUTFILE || token->label == OUTFILE_A))
			find_cmd_outfile(token, ft_lstlast(*cmds)->content, &pb);
		else if (token->label == PIPE)
			add_cmd(token, cmds, &pb);
		curr = curr->next;
	}
	g_glob->cmds = cmds;
}
