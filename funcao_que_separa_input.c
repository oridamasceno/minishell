/*
 * Compilação: "cc -Wall -Wextra -Werror funcao_que_separa_input.c -lreadline". !!!
 *
 * 39 - aspas simples;
 * 34 - aspas duplas;
 * 124 - pipe;
*/

#include "includes.h"
#include "minishell.h"

/*is_space: Essa função verifica se o caractere é um espaço ou uma tab*/

int is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (c);
	return (0);
}

/*find_next_char: Essa função procura o próximo caractere que seja
igual ao caractere colocado em "type". Porém, se type for igual a
"1", a função vai procurar o próximo espaço ou tab*/

int	find_next_char(char *str, int idx, int type)
{
	while (str[idx])
	{
		if (type == 1)
		{
			if (is_space(str[idx]))
				return (idx);
			else if (str[idx + 1] == 34 || str[idx +1] == 39)
				return (++idx);
			else if (!str[idx + 1])
				return (++idx);
		}
		idx++;
		if (str[idx] == type)
				return (idx);
	}
	return (0);
}

/*string_inside_quotes: Essa função pega um vetor iniciado a partir de uma
aspa direcionada por "idx". Ela pega todos os caracteres seguintes até que a
próxima aspa seja encontrada. Caso não tenha próxima aspa, a função retorna
"NULL"*/

char	*string_inside_quotes(char *str, int idx)
{
	int	len;
	int	iret;
	int	closing;
	char	*ret;
	
	closing = find_next_char(str, idx, str[idx]);
	if (!closing)
		return (NULL);
	len = closing - idx;
	ret = (char *) malloc(len * sizeof(char));
	if (!ret)
		return (NULL);
	iret = -1;
	while (++idx < closing)
		ret[++iret] = str[idx];
	ret[iret + 1] = '\0';
	return (ret);
}

/*word_between_spaces: Essa função pega um vetor iniciado a partir de um
caractere direcionada por "idx". Ela pega todos os caracteres seguintes
até que a próxima aspa, espaço, tab ou '\0' seja encontrada.*/

char	*word_between_spaces(char *str, int idx)
{
	int len;
	int closing;
	int iret;
	char *ret;

	closing = find_next_char(str, idx, 1);
	if (!closing)
		return (NULL);
	len = (closing - idx) + 1;
	ret = (char *) malloc(len * sizeof(char));
	iret = -1;
	while (idx < closing)
		ret[++iret] = str[idx++];
	ret[iret + 1] = '\0';
	return (ret);
}

/*input_tokens: Essa função verifica se há aspas fechadas, printa as
palavras separadas e printa os vetores dentro das aspas duplas. Se der
erro com aspas, ela retorna 1 e, se der erro com palavras, ela retorna 2*/

int input_tokens(char *str)
{
	int	i = 0;
	int count = 0;
	char *splited_part;

	while(is_space(str[i]))
		i++;
	while(str[i])
	{
		if(str[i] == 34 || str[i] == 39)
		{
			splited_part = string_inside_quotes(str, i);
			if (!splited_part)
				return (1);
			printf("%d - Achei aspas		|%s|\n", count++, splited_part);
			free(splited_part);
			i = find_next_char(str, i, str[i]);
		}
		else if (!is_space(str[i]))
		{
			splited_part = word_between_spaces(str, i);
			if (!splited_part)
				return (2);
			printf("%d - Achei uma palavra	|%s|\n", count++, splited_part);
			free(splited_part);
			i = find_next_char(str, i, 1) - 1;
		}
		i++;
	}
	return (0);
}