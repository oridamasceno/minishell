/*
 * Compilação: "cc -Wall -Wextra -Werror funcao_que_separa_input.c -lreadline". !!!
 *
 * 39 - aspas simples;
 * 34 - aspas duplas;
 * 124 - pipe;
*/

#include "includes.h"
#include "minishell.h"

int is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (c);
	return (0);
}

int	find_next_char(char *str, int idx, int tipo)
{
	while (str[idx])
	{
		if (tipo == 1)
		{
			if (is_space(str[idx]))
				return (idx);
			else if (str[idx + 1] == 34 || str[idx +1] == 39)
				return (++idx);
			else if (!str[idx + 1])
				return (++idx);
		}
		idx++;
		if (str[idx] == tipo)
				return (idx);
	}
	return (0);
}

char	*string_inside_quotes(char *str, int idx)
{
	int	len;
	int	idx_ret;
	int	fechamento;
	char	*retorno;
	
	fechamento = find_next_char(str, idx, str[idx]);
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

char	*word_between_spaces(char *str, int idx)
{
	int len;
	int ultimo;
	int iret;
	char *ret;

	ultimo = find_next_char(str, idx, 1);
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