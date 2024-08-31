#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "./libft/libft.h"

typedef struct s_token {
	char	*str_token;
	struct s_token *next;
}		t_token;

typedef struct s_quotes {
	int	position;
	int	type_token;
	char	*str_quote;
	struct s_quotes *next;
}		t_quotes;

#endif
