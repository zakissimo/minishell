/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/07 12:42:56 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft/includes/libft.h"

typedef enum e_label
{
	HEREDOC,
	OUTFILE_A,
	PIPE,
	OUTFILE,
	INFILE,
	VARIABLE,
	UNKNOWN
}			t_label;

typedef struct s_token
{
	t_label			label;
	const char		*str;
	int				str_idx;
	int				idx;
	char			*arg;
}				t_token;

typedef struct s_glob
{
	char		**envp;
	char		*input;
	t_list		**head;
}				t_glob;

extern t_glob	*g_glob;

void	print_nodes(void *n);
void	find_var(t_token *token, char *input);
void	free_token_str(void *n);
void	print_label(t_label label);
int		find_quote(const char *s, char c);
char	*ft_strtrimf(char *s1, char const *set);
void	get_ops(const char *input, t_list **head);
int		op_error(const char *input);
void	expand(t_token *var);
int		quote_error(const char *input);
int		get_longest_str(char *s1, char *s2);
void	insert_node(t_list **head, t_list *node, int idx);
void	add_cmd(t_list **head, const char *input, size_t i, size_t end_cmd);

#endif
