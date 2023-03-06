NAME = pipex
BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft/libft.a
SRCS = pipex.c pipex_utils.c pipex_utils2.c $(LIBFT)
SRCS_B = pipex_bonus.c pipex_utils.c pipex_utils2.c $(LIBFT)
OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

all : $(NAME)
$(LIBFT) :
	make -C libft
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus : $(BONUS)
$(BONUS) : $(OBJS_B)
	$(CC) $(CFLAGS) $(OBJS_B) -o $(BONUS)

clean :
	rm -f $(OBJS) $(OBJS_B)

fclean : clean
	rm -rf $(NAME) $(BONUS)

re : fclean all
