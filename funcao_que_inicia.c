/*
#include "includes.h"
#include "minishell.h"
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_teste {
	char token[1000];
	char frase[1000];
	struct s_teste *next;
} t_teste;

int	first_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int main(int ac, char **av, char **ev)
{
	int i  = -1;
	int equal_index;
	t_teste env_list;
	while (ev[++i])
	{
		equal_index = first_equal(ev[i]);
		printf("String do env: %s\n", ev[i]);

		strncpy(env_list.token, ev[i], equal_index);
		env_list.token[equal_index] = '\0';
		printf("Token da struct: %s\n", env_list.token);

		strncpy(env_list.frase, &ev[i][equal_index + 1], sizeof(env_list.frase) - 1);
		env_list.frase[sizeof(env_list.frase) - 1] = '\0';
		printf("Frase da struct: %s\n\n", env_list.frase);
	}
	return (0);
}

/*
int rl_start_function(void)
{
	char	*input;
	int	ret_itokens;

	printf("Bem-vindo ao nosso start!\n");
	printf("Digite 'sair' para sair.\n");

	while (1)
	{
		input = readline("\nnickname@123:~/um/caminho/qualquer$ ");
		add_history(input);

		if (strcmp(input, "sair") == 0)
		{
			free(input);
			break ;
		}

		ret_itokens = input_tokens(input);
		if (ret_itokens == ERROR_QUOTE)
		{
			rl_on_new_line();
			rl_replace_line("Aspas sem fechamento.\n", 0);
			rl_redisplay();
		}
		else if (ret_itokens == ERROR_WORD)
		{
			rl_on_new_line();
			rl_replace_line("Erro na alocação de palavras.\n", 0);
			rl_redisplay();
		}
		free(input);
	}

	rl_clear_history();
	printf("\nPrograma encerrado.\n");

	return (0);
}
*/