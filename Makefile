# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/25 14:09:35 by cnotin            #+#    #+#              #
#    Updated: 2021/04/22 00:48:44 by lgimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS  = -Wall -Wextra -Werror

INC = -I headers/minishell.h

LIB = libft/libft.a

SRCS =  srcs/builtin/ft_cd.c \
		srcs/routine/do_builtin.c \
		srcs/routine/do_chevron.c \
		srcs/routine/del_chevron.c \
		srcs/routine/edit_cmd.c \
		srcs/routine/do_pipe.c \
		srcs/routine/routine.c \
		srcs/builtin/ft_echo.c \
		srcs/builtin/ft_env.c \
		srcs/builtin/ft_exit.c \
		srcs/builtin/ft_export.c \
		srcs/builtin/ft_pwd.c \
		srcs/builtin/ft_unset.c \
		srcs/utils/init_struct.c \
		srcs/main_func/first_check.c \
		srcs/main_func/main.c \
		srcs/main_func/minishell.c \
		srcs/utils/split_cmd.c \
		srcs/utils/split_cmdline.c \
		srcs/utils/shell_init.c \
		srcs/utils/ft_error.c \
		srcs/utils/utils.c \
		srcs/routine/ft_checkpath.c \
		srcs/parse_cmdline/ft_parsecmdline.c \
		srcs/parse_cmdline/parsecmdline_checknewline.c \
		srcs/parse_cmdline/parsecmdline_dollar.c \
		srcs/parse_cmdline/parsecmdline_dollarbis.c \
		srcs/parse_cmdline/parsecmdline_addbslash.c \
		srcs/parse_cmdline/parsecmdline_rmbslash.c \
		srcs/parse_cmdline/parsecmdline_utils.c

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

