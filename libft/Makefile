# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhabri <zhabri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/04 08:44:16 by zhabri            #+#    #+#              #
#    Updated: 2022/11/16 08:08:28 by zhabri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= clang

CFLAGS			= -Wall -Wextra -Werror -Iincludes -fpie

RM				= rm -f

NAME			= libft.a

SRCS			= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
				  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
				  ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
				  ft_lstsize.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
				  ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c \
				  ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
				  ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
				  ft_substr.c ft_tolower.c ft_toupper.c ft_atof.c ft_atol.c

SRCS_PRINTF		= ft_printf.c \
				ft_uputnbr_base.c \
				ft_uputnbr_fd.c \
				print_addr.c \
				arg_lst.c \
				type_check.c

SRCS_GNL		= get_next_line.c get_next_line_utils.c

OBJS			= $(SRCS:.c=.o)

OBJS			+= $(addprefix ft_printf/, $(SRCS_PRINTF:.c=.o))

OBJS			+= $(addprefix gnl/, $(SRCS_GNL:.c=.o))

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			ar -rcs $@ $^

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:
			make fclean
			make

.PHONY:		all clean fclean re
