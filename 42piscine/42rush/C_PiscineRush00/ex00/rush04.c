#include<unistd.h>

void	ft_putchar(char c);

void	rush(int x, int y)
{
	int	b;
	int	a;

	b = 1;
	while (b <= y && x > 0)
	{
		a = 1;
		while (a <= x)
		{
			if ((a == 1 && b == 1) || (b == y && a == x && b != 1 && a != 1))
				ft_putchar('A');
			else if ((a == x && b == 1) || (a == 1 && b == y))
				ft_putchar('C');
			else if (a == 1 || a == x || b == 1 || b == y)
				ft_putchar('B');
			else
				ft_putchar(' ');
			a++;
		}
		ft_putchar('\n');
		b++;
	}
}
