
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:14:40 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/19 11:46:36 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"
#include <stdlib.h>

t_cmd	*init_cmd_token(int in, int out, char *str)
{
	t_cmd	*node;

	node = NULL;
	while (!node)
		node = malloc(sizeof(t_cmd *));
	node->fd_in = in;
	node->fd_out = out;
	node->str = str;
	return (node);
}

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
	node = init_cmd_token(0, 1, NULL);
	if (trimmed && trimmed[0])
	{
		while (trimmed[i] && !str_is_op(trimmed + i))
			i += skip_if_quotes(trimmed, i);
		node->str = ft_substr(trimmed, 0, i);
	}
	ft_lstadd_back(cmds, ft_lstnew(node));
	free(trimmed);
}

void	find_cmd_infile(t_token *token, t_cmd *node)
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
	node->str = ft_strtrimf(ft_strjoinf(ft_strjoinf(node->str, " "), cmd), " \t");
	free(cmd);
	free(token->arg);
	token->arg = remove_quotes(file);
	if (token->label == INFILE)
		node->fd_in = open(token->arg, O_RDONLY);
	else
		node->fd_in = -2;
}
void	find_cmd_outfile(t_token *token, t_cmd *node)
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
	node->str = ft_strtrimf(ft_strjoinf(ft_strjoinf(node->str, " "), cmd), " \t");
	free(cmd);
	free(token->arg);
	token->arg = remove_quotes(file);
	if (token->label == OUTFILE)
		node->fd_out = open(token->arg, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		node->fd_out = open(token->arg, O_RDWR | O_CREAT | O_APPEND, 0644);
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
			find_cmd_infile(token, ft_lstlast(*cmds)->content);
		else if (token->label == OUTFILE || token->label == OUTFILE_A)
			find_cmd_outfile(token, ft_lstlast(*cmds)->content);
		else if (token->label == PIPE && token->arg[0] != '\0')
			ft_lstadd_back(cmds, ft_lstnew(ft_strdup(token->arg)));
		curr = curr->next;
	}
	g_glob->cmds = cmds;
}
