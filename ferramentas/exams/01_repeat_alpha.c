#include <unistd.h>

void	laput(char c)
{
	write (1, &c, 1);
}

void	ralpha(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s >= 'a' && *s <= 'z')
		{
			while (++i <= (*s - 96))
				laput(*s);
		}
		else if (*s >= 'A' && *s <= 'Z')
		{
			while (++i <= (*s - 64))
				laput(*s);
		}
		else
			laput(*s);
		i = 0;
		s++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 2)
		ralpha(av[1]);
	laput('\n');
	return (0);
}
