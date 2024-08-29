#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

void	rot(char *s)
{
	while (*s)
	{
		if ((*s >= 'A' && *s <= 'M') || (*s >= 'a' && *s <= 'm'))
			laput(*s + 13);
		else if ((*s >= 'N' && *s <= 'Z') || (*s >= 'n' && *s <= 'z'))
			laput(*s - 13);
		else
			laput(*s);
		s++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		rot(av[1]);
	laput('\n');
	return (0);
}

