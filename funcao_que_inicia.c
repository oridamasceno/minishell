#include "includes.h"
#include "minishell.h"

int main(void)
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
		if (ret_itokens == 1)
		{
			rl_on_new_line();
			rl_replace_line("Aspas sem fechamento.\n", 0);
			rl_redisplay();
		}
		else if (ret_itokens == 2)
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