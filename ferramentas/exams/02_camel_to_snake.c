#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

void	csnake(char *s)
{
	while (*s)
	{
		if (*s >= 'A' && *s <= 'Z')
		{
			laput('_');
			*s += 32;
		}
		laput(*s);
		s++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		csnake(av[1]);
	laput('\n');
	return (0);
}
