#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_SIZE 1024

# include "includes.h"
# include "./libft/libft.h"

typedef struct s_token {
	char	str_token[MAX_SIZE];
	struct s_token *next;
}		t_token;

#endif
