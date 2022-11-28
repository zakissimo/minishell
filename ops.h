/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:30:45 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/28 09:14:07 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPS_H
# define OPS_H

# include "libft/includes/libft.h"
# include <stdbool.h>

typedef struct s_op
{
	const char	*op;
	int			idx;
}			t_op;

typedef struct s_cmd
{
	const char	*cmd;
	int			idx;
}			t_cmd;

char	*ft_opnstr(const char *big, const char *little, size_t len);
char	*ft_strtrimf(char *s1, char const *set);

#endif
