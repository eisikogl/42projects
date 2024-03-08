#include <unistd.h>

void	ft_print(char num)
{
	write (1, &num, 1);
}

void	ft_print_comb(void)
{
	char	i;
	char	j;
	char	k;

	i = '0';
	while (i <= '7')
	{
		j = i + 1;
		while (j <= '8')
		{
			k = j + 1;
			while (k <= '9')
			{
				ft_print(i);
				ft_print(j);
				ft_print(k);
				if (i == '7' && j == '8' && k == '9')
					break ;
				write (1, ", ", 2);
				k++;
			}
			j++;
		}
		i++;
	}
}
