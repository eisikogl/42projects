#include <unistd.h>

void	print(char c)
{
	write(1, &c, 1);
}

void	ft_rev_int_tab(int *tab, int size)
{
	int	reverse;
	int	i;
	int	swap;

	i = 0;
	reverse = size - 1;
	while (i < size / 2)
	{	
		swap = tab[i];
		tab[i] = tab[reverse];
		tab[reverse] = swap;
		reverse--;
		i++;
	}
}
