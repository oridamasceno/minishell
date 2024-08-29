#include <unistd.h>

void	laput(char c)
{
	write(1, &c, 1);
}

void	lastr(char *s)
{
	while (*s)
		write (1, s++, 1);
}

void	lanbr(int n)
{
	if (n > 9)
	{
		lanbr(n / 10);
		lanbr(n % 10);
	}
	else
		laput(n + '0');
}

int	main(void)
{
	int	i;

	i = 0;
	while (++i <= 100)
	{
		if (((i % 3) == 0) && ((i % 5) == 0))
			lastr("fizzbuzz");
		else if ((i % 3) == 0)
			lastr("fizz");
		else if ((i % 5) == 0)
			lastr("buzz");
		else
			lanbr(i);
		laput('\n');
	}
	return (0);
}
