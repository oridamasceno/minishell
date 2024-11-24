#include "minishell.h"

void	go_start_function(char **ev)
{
	char	*input;
	int		ret_itokens;
	t_env	*env_list;

	env_list = NULL;
	env_list = new_env_lst(ev, env_list);
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
}
