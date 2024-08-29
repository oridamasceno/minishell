#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

void	ul(char *s)
{
	while (*s)
	{
		if (*s >= 'a' && *s <= 'z')
			laput(*s - 32);
		else if (*s >= 'A' && *s <= 'Z')
			laput(*s + 32);
		else
			laput(*s);
		s++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ul(av[1]);
	laput('\n');
	return (0);
}
