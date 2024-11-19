#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_SIZE 1024

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

typedef struct s_env {
	char *key;
	char *str;
	struct s_env *next;
} t_env;

enum {
	ERROR_QUOTE = 3,
	ERROR_WORD,
	SABELA,
};

int is_space(int c);
size_t word_count(char *str);
void	split_free(char **str, size_t o);
int all_quotes_has_end(char *str);
char **split_input_mod(char *str);
int	find_next_char(char *str, int idx);
int input_tokens(char *str);
char	*word_between_spaces(char *str, int idx);

#endif
