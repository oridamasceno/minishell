#include "minishell.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\t')
		return (c);
	return (0);
}

int	redirect_type_idx(char *str, int idx)
{
	while (str[idx])
	{
		if (!(str[idx + 1] == str[idx]))
			return (++idx);
		else if (str[idx + 1] == str[idx])
			return (idx + 2);
		idx++;
	}
	return (idx);
}

int	find_next_char(char *str, int idx)
{
	int	flag;

	flag = 0;
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
		else if (((str[idx] == 124) || (str[idx + 1] == 124)) && flag == 0)
			return (++idx);
		else if ((((str[idx] == 60) || (str[idx + 1] == 60))
				|| ((str[idx] == 62) || (str[idx + 1] == 62))) && flag == 0)
			return (redirect_type_idx(str, idx));
		idx++;
	}
	return (0);
}

size_t	word_count(char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
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

int	all_quotes_has_end(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == 34 || str[i] == 39) && flag == 0)
			flag = str[i];
		else if (str[i] == flag)
			flag = 0;
		i++;
	}
	if (flag == 0)
		return (1);
	return (0);
}
