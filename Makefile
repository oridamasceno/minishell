NAME	=	minishell

CC		= 	cc

CFLAGS	=	-Wall -Wextra -Werror -g

RM		=	rm -f

LIBRARY	=	./libft/

SRCS	=	funcao_que_separa_input.c\
			funcao_que_inicia.c\

all: $(NAME)

libft:
	cd $(LIBRARY) && $(MAKE) bonus && cp -v libft.a ../

minishell: libft
	cc -g $(SRCS) libft.a -lreadline -o $(NAME)

run: re
	./$(NAME)

val: re
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=supressions.supp ./$(NAME)

norm:
	@-norminette -R CheckForbiddenSourceHeader

clean:
	cd $(LIBRARY) && $(MAKE) clean

fclean:	clean
	$(RM) $(NAME)
	$(RM) libft.a
	cd $(LIBRARY) && $(MAKE) fclean

re:	fclean all

.PHONY:	all clean fclean re libft