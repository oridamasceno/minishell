#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_SIZE 1024

# include "includes.h"
# include "./libft/libft.h"

typedef struct s_token {
	char	str_token[MAX_SIZE];
	struct s_token *next;
}		t_token;

enum {
	PIPE = 3,
	SEILA,
	SABELA,
};

int is_space(int c);
int	find_next_char(char *str, int idx, int tipo);
int input_tokens(char *str);
char	*string_inside_quotes(char *str, int idx);
char	*word_between_spaces(char *str, int idx);

#endif
