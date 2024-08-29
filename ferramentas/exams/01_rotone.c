#include <unistd.h>

void	laput(char c)
{
	write(1, &c, 1);
}

void	roto(char *s)
{
	while (*s)
	{
		if ((*s >= 'A' && *s < 'Z') || (*s >= 'a' && *s < 'z'))
			laput(*s + 1);
		else if (*s == 'Z' || *s == 'z')
			laput(*s - 25);
		else
			laput(*s);
		s++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		roto(av[1]);
	laput('\n');
	return (0);
}
