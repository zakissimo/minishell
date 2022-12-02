/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/12/02 10:30:53 by zhabri           ###   ########.fr       */
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
	OP,
	CMD,
	UNKNOWN
}			t_label;

typedef struct s_token
{
	t_label		label;
	char		*str;
	int			idx;
}				t_token;

void	find_ops(const char *input, t_list **head);
void	find_cmds(const char *input, t_list **head);
char	*ft_strtrimf(char *s1, char const *set);
void	insert_node(t_list **head, t_list *node, int idx);

#endif
