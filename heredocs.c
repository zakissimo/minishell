/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:33:11 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/22 14:04:41 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "minishell.h"

static char	*name_generator(void)
{
	int		i;
	char	*file_name;

	i = 0;
	file_name = NULL;
	while (file_name == NULL)
		file_name = malloc(10 * sizeof(char));
	file_name[0] = '.';
	file_name[9] = '\0';
	while (++i < 9)
		file_name[i] = 'a';
	while (file_name == NULL || access(file_name, 0) == 0)
	{
		file_name[8]++;
		i = 9;
		while (--i > 1)
		{
			if (file_name[i] == 'z' + 1)
			{
				file_name[i - 1]++;
				file_name[i] = 'a';
			}
		}
	}
	return (file_name);
}

static char	*get_limiter(t_token *token)
{
	int		i;
	char	*limiter;

	i = 0;
	while (ft_isprint_nospace(token->arg[i]))
	{
		if (token->arg[i] == '"')
			i += find_quote(token->arg + i + 1, '"');
		else if (token->arg[i] == '\'')
			i += find_quote(token->arg + i + 1, '\'');
		i++;
	}
	limiter = ft_substr(token->arg, 0, i);
	return (remove_quotes(limiter));
}

static void	handle_here_doc(t_token *token)
{
	int		fd;
	char	*here_doc_entry;
	char	*file_name;
	char	*limiter;

	file_name = name_generator();
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(file_name);
		return ;
	}
	here_doc_entry = readline("> ");
	limiter = get_limiter(token);
	while (here_doc_entry != NULL
		&& strncmp(limiter, here_doc_entry, ft_strlen(limiter) + 1) != 0)
	{
		ft_putendl_fd(here_doc_entry, fd);
		free(here_doc_entry);
		here_doc_entry = readline("> ");
	}
	eof_limiter_not_found(here_doc_entry, limiter);
	close(fd);
	token->file = file_name;
}

void	scan_heredocs(void)
{
	t_list	*curr;
	t_token	*token;

	curr = *g_glob->head;
	while (curr)
	{
		if (curr->content)
		{
			token = ((t_token *)curr->content);
			if (token->label == HEREDOC)
				handle_here_doc(token);
		}
		curr = curr->next;
	}
}

void	unlink_heredocs(void)
{
	t_list	*curr;
	t_token	*token;

	curr = *g_glob->head;
	while (curr)
	{
		if (curr->content)
		{
			token = ((t_token *)curr->content);
			if (token->label == HEREDOC)
				unlink(token->file);
		}
		curr = curr->next;
	}
}
