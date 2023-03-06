# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/06 13:37:46 by aybiouss          #+#    #+#              #
#    Updated: 2023/02/12 17:19:51 by aybiouss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
NAME=libft.a
CFLAGS=-Wall -Wextra -Werror
OPTION= -c
SRCS= ft_atoi.c	ft_isalpha.c	ft_memchr.c	ft_memset.c	ft_putstr_fd.c	ft_strlcpy.c ft_strrchr.c \
ft_bzero.c	ft_isascii.c	ft_memcmp.c	ft_putchar_fd.c	ft_strchr.c	ft_strlen.c	ft_substr.c \
ft_calloc.c	ft_isdigit.c	ft_memcpy.c	ft_putendl_fd.c	ft_strdup.c	ft_strncmp.c	ft_tolower.c \
ft_isalnum.c	ft_isprint.c	ft_memmove.c ft_putnbr_fd.c ft_strlcat.c ft_toupper.c	ft_strnstr.c \
ft_itoa.c	ft_strtrim.c	ft_strmapi.c	ft_striteri.c	ft_split.c 	ft_strjoin.c\
ft_lstlast_bonus.c	ft_lstnew_bonus.c	ft_lstadd_front_bonus.c	ft_lstsize_bonus.c	ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c	ft_lstclear_bonus.c	ft_lstmap_bonus.c	ft_lstiter_bonus.c \

OBJ = $(SRCS:.c=.o)
BONUS = $(BON:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ) $(BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

