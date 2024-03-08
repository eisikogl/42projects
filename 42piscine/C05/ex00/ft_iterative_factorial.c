int	ft_iterative_factorial(int nb)
{
	int	res;
	int	i;

	if (nb < 0)
		return (0);
	i = 1;
	res = 1;
	while (i < nb + 1)
		res = res * i++;
	return (res);
}
