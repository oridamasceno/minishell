#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

void	sar(char *s, int a, int b)
{
	while (*s)
	{
		if (*s == a)
			laput(b);
		else
			laput(*s);
		s++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 4 && (!av[2][1] && !av[3][1]))
		sar(av[1], av[2][0], av[3][0]);
	laput('\n');
	return (0);
}

