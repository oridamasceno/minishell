#include "includes.h"
#include "minishell.h"

char	*check_all(char *str)
{
	int i;
	int q_idx;
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			q_idx = next_quote(39, str, i);
			split_single_quotes(str, i, q_idx);
		}
	}
}
