# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cnotin <cnotin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 11:42:26 by cnotin            #+#    #+#              #
#    Updated: 2020/08/25 18:27:17 by cnotin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = @gcc

CFLAGS = -Wall -Wextra -Werror 

HEADER = libft.h

SRC = 	ft_strlen.c ft_strdup.c ft_strchr.c ft_strrchr.c ft_strnstr.c \
		ft_strncmp.c ft_strlcat.c ft_substr.c ft_strjoin.c ft_split.c \
		ft_strtrim.c ft_strlcpy.c ft_split.c ft_strmapi.c ft_strmapi.c\
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_strcmp.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memset.c \
		ft_memmove.c ft_memalloc.c ft_memchr.c ft_memcmp.c \
		ft_calloc.c ft_atoi.c ft_strnew.c ft_strncpy.c ft_strnjoinf.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_strdel.c ft_strcat.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_itoa_base.c \
		ft_free_tab.c ft_strncat.c ft_strcpy.c \
		get_next_line.c ft_putchar.c

BSRC = 	ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstadd_back.c \
		ft_lstclear.c \
		ft_lstadd_front.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstsize.c \
		ft_lstlast.c 

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

all : $(NAME)

$(NAME) :	$(OBJ)
				@ar rc $(NAME) $(OBJ)
				@ranlib $(NAME)
			
bonus :	$(BOBJ) $(NAME)
			@ar rc $(NAME) $(BOBJ)
		
clean :
		@rm -rf $(OBJ) $(BOBJ)
	
fclean : clean
		@rm -rf $(NAME)
	
re : fclean all

.PHONY : all clean fclean re
