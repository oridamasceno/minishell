#include "includes.h"
#include "minishell.h"

/*
 * 39 - aspas simples = 1;
 * 34 - aspas duplas = 2;
*/
/*
int contador_de_aspas(char *str)
{
	int flag = 0;
	while (*str)
	{
		if (*str == 39)
			flag++;
		str++;
	}
	if ((flag % 2) != 0)
		return (-1);
	else if (flag == 0)
		return (0);
	else
		return (flag);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		int ret = contador_de_aspas(av[1]);
		if (ret == -1)
			printf("Quantidade de aspas é impar, vai dar erro\n");
		else if (ret == 0)
			printf("Sem aspas simples! :)\n");
		else
			printf("Quantidade de aspas: %d\n", ret);
	}
	return (0);
}
*/
int	check_quotes_marks(char *str)
{
}

void	separador_input(char *str)
{
	if (!str)
		return (-1);
	while(str)
	{
	}
}
