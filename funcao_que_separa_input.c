/*
 * Compilação: "cc -Wall -Wextra -Werror funcao_que_separa_input.c -lreadline". !!!
 *
 * 39 - aspas simples = 1;
 * 34 - aspas duplas = 2;
*/

#include "includes.h"
#include "minishell.h"

int	essa_aspa_tem_fechamentoP(char *str, int idx)
{
	int	tipo = str[idx];
	while (str[++idx])
	{
		if (str[idx] == tipo)
			return (idx);
	}
	return (0);
}

char	*frase_dentro_das_aspas(char *str, int idx)
{
	int	len;
	int	idx_ret;
	int	fechamento;
	char	*retorno;
	
	fechamento = essa_aspa_tem_fechamentoP(str, idx);
	if (!fechamento)
		return (NULL);
	len = (fechamento - idx);
	retorno = (char *) malloc(len * sizeof(char));
	if (!retorno)
		return (NULL);
	idx_ret = -1;
	while (++idx < fechamento)
		retorno[++idx_ret] = str[idx];
	retorno[idx_ret + 1] = '\0';
	return (retorno);
}

int main(void)
{
	char	*input;
	char	*aspas;
	int	i;

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

		i = 0;
		while (input[i])
		{
			if (input[i] == 34 || input[i] == 39)
			{
				aspas = frase_dentro_das_aspas(input, i);
				if (!aspas)
				{
					rl_on_new_line();
					rl_replace_line("Aspas sem fechamento.\n", 0);
					rl_redisplay();
				}
				else
				{
					printf("%s|\n", aspas);
					free(aspas);
					i = essa_aspa_tem_fechamentoP(input, i);
				}
			}
			i++;
		}
		free(input);
	}

	rl_clear_history();
	printf("\nPrograma encerrado.\n");

	return (0);
}
