#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "check.h"
#include "func.h"
#include "numbers.h"

int	jump_to_dict(int len, int file_d)
{
	char	ch;
	int		i;

	while (1)
	{
		while (1)
		{
			if (read(file_d, &ch, 1) < 1)
				return (0);
			if (ch == '1')
				break ;
		}
		i = 0;
		while (1)
		{
			if (read(file_d, &ch, 1) < 1)
				return (0);
			if (ch != '0')
				break ;
			i++;
		}
		if (i == len - 1)
			break ;
	}
	return (1);
}

void	initial_digits(char *gb, char *tp, int len, char *str)
{
	(void)tp;
	if (len == 2 && *str >= '2')
	{
		gb[0] = 0;
		gb[1] = *str;
		gb[2] = '0';
		gb[3] = ':';
	}
	else if (len == 2)
	{
		gb[0] = 0;
		gb[1] = *str;
		gb[2] = *(str + 1);
		gb[3] = ':';
	}
	else
	{
		gb[0] = 0;
		gb[1] = *str;
		gb[2] = ':';
	}
}

int	jump_to_line(int len, char *str, int file_d)
{
	int		t;
	char	gb[4];
	char	tp[4];

	if (len > 2)
	{
		if (!jump_to_dict(len, file_d))
			return (0);
		return (1);
	}
	initial_digits(gb, tp, len, str);
	while (1)
	{
		t = 0;
		while (t < len + 1)
		{
			tp[t] = tp[t + 1];
			t++;
		}
		if (read(file_d, &tp[len + 1], 1) < 1)
			return (0);
		if (ft_strcmp(&gb[1], &tp[1], len + 1) && (gb[0] < '0' || gb[0] > '9'))
			return (1);
	}
	return (1);
}

int	write_number(int file_d, char **mem)
{
	int		i;
	char	ch;

	i = 0;
	while (1)
	{
		if (read(file_d, &ch, 1) < 1)
			return (0);
		if (ch == '\n')
			return (0);
		if (is_alpha(ch))
			break ;
	}
	while (1)
	{
		**mem = ch;
		(*mem)++;
		if (read(file_d, &ch, 1) < 1)
			return (1);
		if (ch == '\n' || ch == '\0')
			break ;
	}
	return (1);
}

int	send_number(int ln, char *str, char *file_name, char **mem)
{
	int	i;
	int	fd;

	fd = open(file_name, O_RDONLY);
	i = 0;
	if (fd < 1)
		return (0);
	if (!jump_to_line(ln, str, fd))
		return (0);
	if (!write_number(fd, mem))
		return (0);
	**mem = ' ';
	(*mem)++;
	**mem = '\n';
	close(fd);
	return (1);
}
