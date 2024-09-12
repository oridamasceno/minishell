/*
 * Compilação: "cc -Wall -Wextra -Werror funcao_que_separa_input.c -lreadline". !!!
 *
 * 39 - aspas simples;
 * 34 - aspas duplas;
 * 124 - pipe;
*/

#include "includes.h"
#include "minishell.h"

int	lalen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

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

/*w_count: Essa função conta a quantidade de palavras dentro do input.*/
size_t w_count(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		if(str[i] == 34 || str[i] == 39)
		{
			i = find_next_char(str, i, str[i]);
			count++;
		}
		else if (!is_space(str[i]))
		{
			i = find_next_char(str, i, 1) - 1;
			count++;
		}
		i++;
	}
	return (count);
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
	ret = (char *) ft_calloc(len, sizeof(char *));
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
	ret = (char *) ft_calloc(len, sizeof(char *));
	iret = -1;
	while (idx < closing)
		ret[++iret] = str[idx++];
	ret[iret + 1] = '\0';
	return (ret);
}

void	w_free(char **str, size_t o)
{
	size_t	i;

	i = 0;
	while (i < o)
	{
		free(str[i]);
		i++;
	}
	free(str);
}


char **split_input_mod(char *str)
{
	int i_str;
	int i_ret;
	char **ret;

	i_str = 0;
	i_ret = 0;
	if (!str)
		return (NULL);
	ret = (char **) ft_calloc(w_count(str), sizeof(char *));
	if (!ret)
		return (NULL);
	while (ret && str[i_str])
	{
		if(str[i_str] == 34 || str[i_str] == 39)
		{
			ret[i_ret] = string_inside_quotes(str, i_str);
			if (!ret[i_ret])
			{
				w_free(ret, i_ret);
				return (NULL);
			}
			printf("Achei aspas		|%s|\n", ret[i_ret]);
			i_str = find_next_char(str, i_str, str[i_str]);
			i_ret++;
		}
		else if (!is_space(str[i_str]))
		{
			ret[i_ret] = word_between_spaces(str, i_str);
			if (!ret[i_ret])
			{
				w_free(ret, i_ret);
				return (NULL);
			}
			printf("Achei uma palavra	|%s|\n", ret[i_ret]);
			i_str = find_next_char(str, i_str, 1) - 1;
			i_ret++;
		}
		i_str++;
	}
	ret[i_ret] = NULL;
	return (ret);
}

/*input_tokens: Essa função verifica se há aspas fechadas, printa as
palavras separadas e printa os vetores dentro das aspas duplas. Se der
erro com aspas, ela retorna 1 e, se der erro com palavras, ela retorna 2*/

int input_tokens(char *str)
{
	int	i = 0;
	int count = -1;
	char **splited;

	splited = split_input_mod(str);
	if (!splited)
		return (2);
	else
	{
		printf("Sucesso!\n");
		while (splited[i] != NULL)
		{
			printf("%d - |%s|\n", ++count, splited[i]);
			i++;
			printf("%i", SABELA);
		}
	}
	return (0);
}