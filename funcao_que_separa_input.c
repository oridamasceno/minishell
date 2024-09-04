/*
 * Compilação: "cc -Wall -Wextra -Werror funcao_que_separa_input.c -lreadline". !!!
 *
 * 39 - aspas simples;
 * 34 - aspas duplas;
 * 124 - pipe;
*/

#include "includes.h"
#include "minishell.h"

int tem_espaco(int c)
{
	if (c == ' ' || c == '\t')
		return (c);
	return (0);
}

int	essa_aspa_tem_fechamentoP(char *str, int idx, int tipo)
{

	while (str[++idx])
	{
		if (tipo == 1)
		{
			if (tem_espaco(str[idx]))
				return (idx);
			else if(!str[idx + 1])
				return (++idx);
		}
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
	
	fechamento = essa_aspa_tem_fechamentoP(str, idx, str[idx]);
	if (!fechamento)
		return (NULL);
	len = fechamento - idx;
	retorno = (char *) malloc(len * sizeof(char));
	if (!retorno)
		return (NULL);
	idx_ret = -1;
	while (++idx < fechamento)
		retorno[++idx_ret] = str[idx];
	retorno[idx_ret + 1] = '\0';
	return (retorno);
}

char	*palavra_unica(char *str, int idx)
{
	int len;
	int ultimo;
	int iret;
	char *ret;

	ultimo = essa_aspa_tem_fechamentoP(str, idx, 1);
	if (!ultimo)
		return (NULL);
	len = (ultimo - idx) + 1;
	ret = (char *) malloc(len * sizeof(char));
	iret = -1;
	while (idx < ultimo)
		ret[++iret] = str[idx++];
	ret[iret + 1] = '\0';
	return (ret);
}

/*----------------------------------------------------------------------*/

int input_tokens(char *str)
{
	int	i = 0;
	int count = 0;
	char *unico;

	while(tem_espaco(str[i]))
		i++;
	while(str[i])
	{
		if(str[i] == 34 || str[i] == 39)
		{
			unico = frase_dentro_das_aspas(str, i);
			if (!unico)
				return (1);
			printf("%d - Achei aspas		|%s|\n", count++, unico);
			free(unico);
			i = essa_aspa_tem_fechamentoP(str, i, str[i]);
		}
		else if (!tem_espaco(str[i]))
		{
			unico = palavra_unica(str, i);
			if (!unico)
				return (2);
			printf("%d - Achei uma palavra	|%s|\n", count++, unico);
			free(unico);
			i = essa_aspa_tem_fechamentoP(str, i, 1);
		}
		i++;
	}
	return (0);
}

/*-----------------------------------------------------------------------*/

int main(void)
{
	char	*input;
	char	*aspas;
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
