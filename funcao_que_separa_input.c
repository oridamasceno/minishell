/*
 * !!! Necessário compilação a flag "-lreadline". !!!
 *
 * 39 - aspas simples = 1;
 * 34 - aspas duplas = 2;
*/

#include "includes.h"
#include "minishell.h"

int	next_quote(int type, char *str, int idx)
{
	while (str[++idx])
	{
		if (str[idx] == type)
			return (idx);
	}
	return (0);
}

int	check_single_quotes(char *str)
{
	int	flag;

	flag = 0;
	while (*str)
	{
		if ((*str == 34 || *str == 39) && flag == 0)
			flag = *str;
		else if ((*str == 34 || *str == 39) && flag == *str)
			flag = 0;
		str++;
	}
	if (flag == 0)
		return (1);
	else
		return (0);
}

int main(void)
{
	char	*input;
	int	ret;

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

		ret = check_single_quotes(input);
		if (ret)
		{
			rl_on_new_line();
			rl_replace_line("Aspas ok.\n", 0);
			rl_redisplay();
		}
		else if (!ret)
		{
			rl_on_new_line();
			rl_replace_line("Aspas sem fechamento.\n", 0);
			rl_redisplay();
		}
		free(input);
	}

	rl_clear_history();
	printf("\nPrograma encerrado.\n");

	return (0);
}
