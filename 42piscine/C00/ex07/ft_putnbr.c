#include <unistd.h>

void	ft_print(char nbc)
{
	write(1, &nbc, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putnbr(nb / 10);
		ft_print('8');
	}
	else if (nb < 0)
	{
		nb *= -1;
		ft_print('-');
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
	}
	if (nb != -2147483648)
		ft_print('0' + nb % 10);
}
