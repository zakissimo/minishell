/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/12 12:49:16 by zhabri           ###   ########.fr       */
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
	char			*not_expanded;
}				t_token;

typedef struct s_glob
{
	t_list		**envp;
	char		*input;
	t_list		**head;
	t_list		**cmds;
}				t_glob;

extern t_glob	*g_glob;

void	get_cmd(void);
void	nuke_glob(void);
void	free_op_list(void);
void	get_args(void);
void	get_after_op(void);
int		ft_isprint_nospace(int c);
int		ft_isprint_nospace_nodollar(int c);
void	print_cmd(void *n);
void	print_nodes(void *n);
void	find_var(t_token *token, char *input);
void	free_token_str(void *n);
void	print_label(t_label label);
char	*remove_quotes(char *str);
int		find_quote(const char *s, char c);
char	*ft_strjoinf(char *s1, char const *s2);
char	*ft_strtrimf(char *s1, char const *set);
void	get_ops(const char *input, t_list **head);
int		op_error(void);
void	expand(t_token *var);
t_list	**str_tab_to_list(char **tab);
int		quote_error(const char *input);
int		get_longest_str(char *s1, char *s2);
void	insert_node(t_list **head, t_list *node, int idx);
void	add_cmd(t_list **head, const char *input, size_t i, size_t end_cmd);

#endif
