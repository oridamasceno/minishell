#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

int	laspace(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	fword(char *s)
{
	int	i;
	i = 0;
	while (laspace(s[i]))
		i++;
	while (s[i] && !laspace(s[i]))
		laput(s[i++]);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		fword(av[1]);
	laput('\n');
	return (0);
}
