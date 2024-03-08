#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int	ans;

	ans = 0;
	while (str[ans])
		ans++;
	return (ans);
}

int	base_kontrol(char *base)
{
	char	*temp;
	int		i;
	int		j;

	temp = base;
	if (base == 0 || ft_strlen(base) <= 1)
		return (0);
	while (*temp)
	{
		if (*temp == '\t' || *temp == '\n' || *temp == '\v' || *temp == '\f'
			|| *temp == '\r' || *temp == ' ' || *temp == '+' || *temp == '-')
			return (0);
		temp++;
	}
	i = 0;
	while (i < temp - base)
	{
		j = i + 1;
		while (j < temp - base)
			if (base[i] == base[j++])
				return (0);
		i++;
	}
	return (1);
}

void	solve(int nbr, char *base, int bolen)
{
	if (nbr == -2147483648)
	{
		solve(nbr / bolen, base, bolen);
		ft_putchar(*(base - (nbr % bolen)));
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar('-');
		solve(-nbr, base, bolen);
		return ;
	}
	if (nbr > bolen - 1)
		solve(nbr / bolen, base, bolen);
	ft_putchar(*(base + nbr % bolen));
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	bolen;

	if (base_kontrol(base) == 0)
	{
		return ;
	}
	bolen = ft_strlen(base);
	solve(nbr, base, bolen);
}
