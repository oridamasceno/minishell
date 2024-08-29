#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

int	lalen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	revp(char *s)
{
	int	i;

	i = lalen(s);
	while (s[--i])
		write (1, &s[i], 1);
}

int	main(int ac, char **av)
{
	if (ac == 2)
		revp(av[1]);
	laput('\n');
	return (0);
}
