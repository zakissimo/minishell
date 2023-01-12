/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:33:11 by zhabri            #+#    #+#             */
/*   Updated: 2023/01/12 14:07:27 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	finalize_heredoc(char *here_doc_entry, char *limiter, \
		int fd, int stdin_cpy)
{
	if (!g_glob->sig_int)
		eof_limiter_not_found(here_doc_entry, limiter);
	close(fd);
	free(limiter);
	dup2(stdin_cpy, 0);
	close(stdin_cpy);
}

static int	init_heredoc(char **here_doc_entry, char **file_name, \
		int *stdin_cpy, int *fd)
{
	*file_name = name_generator();
	*stdin_cpy = dup(0);
	*fd = open(*file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
	{
		free(*file_name);
		return (1);
	}
	*here_doc_entry = NULL;
	return (0);
}

static void	handle_here_doc(t_token *token)
{
	int		fd;
	int		stdin_cpy;
	char	*here_doc_entry;
	char	*file_name;
	char	*limiter;

	limiter = get_limiter(token);
	if (init_heredoc(&here_doc_entry, &file_name, &stdin_cpy, &fd))
		return ;
	g_glob->here_doc = true;
	while (!g_glob->sig_int)
	{
		here_doc_entry = readline("> ");
		if (!here_doc_entry || g_glob->sig_int \
			|| !strncmp(limiter, here_doc_entry, ft_strlen(limiter) + 1))
			break ;
		ft_putendl_fd(here_doc_entry, fd);
		free(here_doc_entry);
	}
	g_glob->here_doc = false;
	finalize_heredoc(here_doc_entry, limiter, fd, stdin_cpy);
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
			if (token->label == HEREDOC && token->file)
				unlink(token->file);
		}
		curr = curr->next;
	}
}
