NAME = minishell.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = funcao_que_separa_input.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -I . -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs minishell.a $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus