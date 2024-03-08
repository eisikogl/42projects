int	ft_str_is_lowercase(char *str)
{
	int	check;

	check = 0;
	while (*str != '\0')
	{
		if (*str >= 'a' && *str <= 'z')
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
