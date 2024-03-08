#include <stdio.h>
#include <unistd.h>

void	ft_print(char a)
{
	write(1, &a, 1);
}

void	ft_print_comb2(void)
{
	int	a;
	int	b;

	a = 0;
	b = 1;
	while (a <= 98)
	{
		b = a + 1;
		while (b <= 99)
		{
			ft_print('0' + a / 10);
			ft_print('0' + a % 10);
			ft_print(' ');
			ft_print('0' + b / 10);
			ft_print('0' + b % 10);
			if (a == 98 && b == 99)
			{
				break ;
			}
			ft_print(',');
			ft_print(' ');
			b++;
		}
		a++;
	}
}
/*
int	main(void)
{
	ft_print_comb2();
} */
