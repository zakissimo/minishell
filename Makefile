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

SRCS		= add_cmd.c \
				arg.c \
				builtin.c \
				cd.c \
				dollar.c \
				echo.c \
				env.c \
				errors.c \
				exit.c \
				export.c \
				find_cmd.c \
				find_ops.c \
				ft_atoll.c \
				ft_split_quotes.c \
				ft_split_sep.c \
				ft_strjoinf.c \
				ft_strtrimf.c \
				get_after.c \
				get_sum.c \
				heredocs.c \
				insert_node.c \
				main_utils.c \
				minishell.c \
				nuke.c \
				open.c \
				pipe_error.c \
				pipex.c \
				pipex_children.c \
				print.c \
				pwd.c \
				signal.c \
				split_cmds.c \
				unset.c \
				utils.c \
				utils_bis.c \
				utils_cd.c \
				utils_exit.c \
				utils_export.c \
				utils_heredocs.c \
				utils_pipex.c \
				utils_signal.c \
				utils_ter.c			

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
