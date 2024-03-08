#include <unistd.h>

void	print(char c)
{
	write(1, &c, 1);
}

void	ft_print_combn(int n)
{
	if (n > 0)
		print('0' + n % 10);
	print(',');
	print(' ');
}

void	ft_makecombn(int i)
{
	if (i > 0 && i <= 99)
		ft_makecombn(i - 1);
	ft_takecombn();
}

void	ft_takecombn(int j)
{
	if (j > 9)
	{
		ft_putnbr(j / 10);
	}
	ft_print('0' + j % 10);
}
