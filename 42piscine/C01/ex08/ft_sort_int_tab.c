#include <unistd.h>
#include <stdio.h>

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	hld;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				hld = tab[i];
				tab[i] = tab[j];
				tab[j] = hld;
			}			
			j++;
		}
		i++;
	}
}
