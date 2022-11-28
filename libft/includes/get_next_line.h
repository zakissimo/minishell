/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:27:00 by zhabri            #+#    #+#             */
/*   Updated: 2022/11/16 08:53:53 by zhabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif

char		*get_next_line(int fd);
int			nl_in_str(char *str);
int			ft_strlen(char *str);
char		*ft_strdup(char *buf);
char		*ft_rejoin(char *stash, char *buf);
char		**split_to_tab(char **tab, int nl_idx, char *stash);
char		*ft_rejoin(char *stash, char *buf);

#endif
