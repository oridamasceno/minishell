#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

void	amirr(char *s)
{
	while (*s)
	{
		if ((*s >= 'A') && (*s <= 'Z'))
			laput('M' - (*s - 'N'));
		else if ((*s >= 'a') && (*s <= 'z'))
			laput('m' - (*s - 'n'));
		else
			laput(*s);
		s++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		amirr(av[1]);
	laput('\n');
	return (0);
}
