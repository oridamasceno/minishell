/*
 * !!! Necessário compilação a flag "-lreadline". !!!
*/

#include "includes.h"
#include "minishell.h"



int main(void)
{
	char	*input;
	char	**break_input;
	int		i;

	printf("Bem-vindo ao programa de exemplo readline!\n");
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

		break_input = ft_split(input, ''')
        /*
        pegar essa função e tirar os espaço. Rever algumas quetões feitas
        no exame-rank2.
        */

		i = -1;
		while (break_input[++i])
		{
			rl_on_new_line();
			rl_replace_line(break_input[i], 0);
			rl_redisplay();
			write(1, "\n", 1);
			free(break_input[i]);
		}
		free(break_input);
		free(input);
	}

	rl_clear_history();
	printf("\nPrograma encerrado.\n");

	return (0);
}
