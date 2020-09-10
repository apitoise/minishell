# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 14:09:35 by cnotin            #+#    #+#              #
#    Updated: 2020/08/25 22:40:03 by cnotin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS  = -Wall -Wextra -Werror

INC = -I headers/minishell.h

LIB = libft/libft.a

SRCS =  srcs/ft_cd.c \
		srcs/ft_echo.c \
		srcs/ft_env.c \
		srcs/ft_exit.c \
		srcs/ft_export.c \
		srcs/ft_pwd.c \
		srcs/ft_unset.c \
		srcs/init_struct.c \
		srcs/main.c \
		srcs/shell_init.c \
		srcs/ft_error.c \
		srcs/utils.c 

OBJS = $(SRCS:.c=.o)


all: $(LIB) $(NAME)

$(NAME): $(OBJS) $(LIB)
		 $(CC) $(CFLAG) -o $(NAME) $(OBJS) $(LIB)

$(LIB):
		@make -C libft/ fclean
		@make -C ./libft
		#@echo "\033[0;34mCompilation libft \033[0m \033[0;32m [OK] \033[0m"

clean:
		@make -C libft/ clean
		@rm -rf $(OBJS)

fclean: clean
		@make -C libft/ fclean
		@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all

