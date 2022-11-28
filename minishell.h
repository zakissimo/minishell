/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/28 11:01:34 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/includes/libft.h"
# include <stdbool.h>

typedef enum e_label
{
	OP,
	CMD
}			t_label;

typedef struct s_token
{
	t_label		label;
	char		*str;
	int			idx;
}				t_token;

char	*ft_strtrimf(char *s1, char const *set);

#endif
