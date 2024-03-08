int	ft_str_is_numeric(char *str)
{
	int	check;

	check = 0;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			check = 0;
		else
		{
			check = 1;
			break ;
		}
		str++;
	}
	if (check == 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}	
}
