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

typedef struct s_env
{
	char	*key;
	char	*str;
	struct s_env	*next;
}			t_env;

typedef struct s_token
{
	char	*token;
	char	*first_cmd;
	char	cmd;
	char	*path;
	struct s_token	*next;
}			t_token;

enum
{
	ERROR_QUOTE = 3,
	ERROR_WORD,
	SABELA,
};

//funcao_que_inicia
void	go_start_function(char **ev);

//utils_separa_input
int		is_space(int c);
size_t	word_count(char *str);
int		redirect_type_idx(char *str, int idx);
int		find_next_char(char *str, int idx);
int		all_quotes_has_end(char *str);

//split_separa_input
char	*word_between_spaces(char *str, int idx);
void	split_free(char **str, size_t o);
char	**split_input_mod(char *str);
int		input_tokens(char *str);

//funcao_cria_nova_env
t_env	*new_env_lst(char **ev, t_env *env_list);

//utils_env
t_env	*my_lstlast(t_env *lst);
void	my_lstadd_back(t_env **lst, t_env *new);
t_env	*my_lstnew(char *first_str, char *second_str);
void	free_env(t_env *list);

#endif
