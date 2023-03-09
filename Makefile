CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g2
READ = -L/goinfre/sben-ela/homebrew/opt/readline/lib
INCLUDE = -I/goinfre/sben-ela/homebrew/opt/readline/include
PROG = mini_shell
LIBFT = Libft/libft.a
PARSING = parse_redirect.c  handle_quotes.c  expanding.c  parse.c parse_read.c parse_line.c
BUILTIN = cd_builtin.c echo_builtin.c env_builtin.c exit_builtin.c export_builtin.c pwd_builtin.c unset_builtin.c
UTILS = env_utils.c  environment.c  ft_error.c  ft_split_v2.c utils1.c utils2.c utils3.c
EXECUTE = ft_execute.c
SOURCES = $(addprefix ./parsing/,$(PARSING))\
	$(addprefix ./builtin/,$(BUILTIN))\
	$(addprefix ./utils/,$(UTILS))\
	$(addprefix ./execute/,$(EXECUTE))\
	$(LIBFT)\
	mini_shell.c 

OBJECTS = $(SOURCES:.c=.o)

all : $(PROG)
$(PROG) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJECTS) -lreadline $(READ)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
$(LIBFT) :
	make -C ./Libft

clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(PROG) $(LIBFT)
	make -C libft fclean

bonus: all
	ar rc $(NAME)

re: fclean all