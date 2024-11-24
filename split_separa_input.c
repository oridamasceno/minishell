#include "minishell.h"

char	*word_between_spaces(char *str, int idx)
{
	int		len;
	int		closing;
	int		iret;
	char	*ret;

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

char	**split_input_mod(char *str)
{
	int		i_str;
	int		i_ret;
	char	**ret;

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

int	input_tokens(char *str)
{
	int		i;
	int		count;
	char	**splited;

	i = 0;
	count = -1;
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
