#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 08:44:16 by zhabri            #+#    #+#              #
#    Updated: 2023/01/03 13:17:27 by zhabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -I. -g

LIBFTFLAGS	= -Llibft -lft -Ilibft/includes

RM			= rm -f

NAME		= minishell

SRCS		= minishell.c \
				find_ops.c \
				ft_strtrimf.c \
				insert_node.c \
				print.c \
				errors.c \
				nuke.c \
				utils.c \
				utils_bis.c \
				utils_ter.c \
				dollar.c \
				arg.c \
				get_after.c \
				ft_strjoinf.c \
				find_cmd.c \
				ft_split_quotes.c \
				split_cmds.c \
				pipe_error.c \
				open.c \
				add_cmd.c \
				heredocs.c \
				pipex.c \
				pipex_children.c \
				utils_pipex.c \
				signal.c \
				main_utils.c \
				get_sum.c \
				utils_heredocs.c \
				utils_signal.c \
				pwd.c \
				exit.c \
				utils_exit.c \
				ft_atoll.c \
				ft_split_sep.c \
				builtin.c \
				echo.c \
				cd.c

OBJS		= $(SRCS:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			@make --no-print-directory -sC libft
			$(CC) $(CFLAGS) $(OBJS) $(LIBFTFLAGS) -lreadline -o $@

all:		$(NAME)

clean:
			make clean -sC libft
			$(RM) $(OBJS)

fclean:		clean
			make fclean -sC libft
			$(RM) $(NAME)

re:
			make fclean
			make all

.PHONY:		all clean fclean re
