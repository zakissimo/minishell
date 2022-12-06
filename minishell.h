/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/06 14:01:09 by zhabri           ###   ########.fr       */
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
	bool			in_single;
	bool			in_double;
}				t_token;

void	print_nodes(void *n);
void	free_token_str(void *n);
void	print_label(t_label label);
int		find_quote(const char *s, char c);
char	*ft_strtrimf(char *s1, char const *set);
void	get_ops(const char *input, t_list **head);
int		op_error(const char *input);
int		quote_error(const char *input);
void	insert_node(t_list **head, t_list *node, int idx);
void	add_cmd(t_list **head, const char *input, size_t i, size_t end_cmd);

#endif
