#include <stdio.h>
#include <unistd.h>

void	ft_print(char num)
{
	write (1, &num, 1);
}

void	ft_print_numbers(void)
{	
	char	numbers;

	numbers = '0';
	while (numbers <= '9')
	{
		ft_print(numbers);
		numbers++;
	}
}
/*
int	main(void)
{
	ft_print_numbers();
}
*/
