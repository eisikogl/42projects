#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "check.h"
#include "func.h"
#include "numbers.h"

int	errors(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.' || str[i] == '-')
		{
			write(1, "Error\n", 6);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_zero(char *str, char *fname, int len)
{
	char	*p;
	char	*c;
	int		i;

	i = 0;
	while (str[i] != 0 && i < len)
		if (str[i++] != '0')
			return (0);
	p = malloc(2048);
	c = p;
	if (!send_number(1, str, fname, &p))
	{
		free(c);
		return (0);
	}
	*(p - 1) = '\n';
	i = 0;
	while (c[i] != '\n')
	{
		write(1, &c[i], 1);
		i++;
	}
	free(c);
	write(1, "\n", 1);
	return (1);
}

int	edit(char **str)
{
	int	i;

	i = 0;
	while (**str <= ' ')
	{
		if (**str == '\n')
			return (0);
		(*str)++;
	}
	if (**str == '+')
		(*str)++;
	if (**str < '0' || **str > '9')
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	char	*filename;

	filename = "numbers.dict";
	if (argc >= 2)
	{
		if (argc == 3)
			filename = argv[argc - 2];
		if (!edit(&argv[argc - 1]))
		{
			write(1, "Error\n", 6);
			return (0);
		}	
		if (!errors(argv[argc - 1]))
			return (0);
		if (check_zero(argv[argc - 1], filename, ft_strlen(argv[1])))
			return (0);
		if (!putnbr (argv[argc - 1], filename, ft_strlen(argv[1])))
		{
			write(1, "Dict Error\n", 11);
			return (0);
		}
	}
	else
		write(1, "Error\n", 6);
	return (0);
}
