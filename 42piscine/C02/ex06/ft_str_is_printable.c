int	ft_str_is_printable(char *str)
{
	int	check;

	check = 0;
	while (*str != '\0')
	{
		if (*str >= 32 && *str <= 127)
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
