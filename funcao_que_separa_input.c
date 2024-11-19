/*
 * 39 - aspas simples;
 * 34 - aspas duplas;
 * 124 - pipe;
*/

#include "minishell.h"

int is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (c);
	return (0);
}

int	find_next_char(char *str, int idx)
{
	int flag = 0;
	while (str[idx])
	{
		if ((str[idx] == 34 || str[idx] == 39) && flag == 0)
			flag = str[idx];
		else if (str[idx] == flag)
			flag = 0;
		if (is_space(str[idx]) && flag == 0)
			return (idx);
		else if ((!str[idx + 1]) && flag == 0)
			return (++idx);
		idx++;
	}
	return (0);
}

size_t word_count(char *str)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		if (!is_space(str[i]))
		{
			i = find_next_char(str, i) - 1;
			count++;
		}
		i++;
	}
	return (count);
}

char	*word_between_spaces(char *str, int idx)
{
	int len;
	int closing;
	int iret;
	char *ret;

	closing = find_next_char(str, idx);
	if (!closing)
		return (NULL);
	len = (closing - idx) + 1;
	ret = (char *) ft_calloc(len, sizeof(char));
	if (!ret)
		return (NULL);
	iret = -1;
	while (idx < closing)
		ret[++iret] = str[idx++];
	ret[iret + 1] = '\0';
	return (ret);
}

void	split_free(char **str, size_t o)
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

int all_quotes_has_end(char *str)
{
	int i = 0;
	int flag = 0;
	while (str[i] != '\0')
	{
		if((str[i] == 34 || str[i] == 39) && flag == 0)
			flag = str[i];
		else if(str[i] == flag)
			flag = 0;
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
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
	ret = (char **) ft_calloc(word_count(str) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (ret && str[i_str])
	{
		if (!is_space(str[i_str]))
		{
			ret[i_ret] = word_between_spaces(str, i_str);
			if (!ret[i_ret])
			{
				split_free(ret, i_ret);
				return (NULL);
			}
			printf("Achei uma palavra	|%s|\n", ret[i_ret]);
			i_str = find_next_char(str, i_str) - 1;
			i_ret++;
		}
		i_str++;
	}
	ret[i_ret] = NULL;
	return (ret);
}

int input_tokens(char *str)
{
	int	i = 0;
	int count = -1;
	char **splited;

	if (!all_quotes_has_end(str))
		return (ERROR_QUOTE);
	splited = split_input_mod(str);
	if (!splited)
		return (ERROR_WORD);
	else
	{
		printf("Sucesso!\n");
		while (splited[i] != NULL)
		{
			printf("%d - |%s|\n", ++count, splited[i]);
			i++;
		}
		split_free(splited, i);
	}
	
	return (0);
}
