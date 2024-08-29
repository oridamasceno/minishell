#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "./libft/libft.h"

typedef struct s_token {
	char	*str_token = NULL;
	struct s_token *next;
}		t_token;

#endif
