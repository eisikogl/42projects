#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "check.h"
#include "func.h"
#include "numbers.h"

int	begin_func(int *len_s, char **str, char *file_name, char **mem)
{
	if (*len_s == 3)
	{
		if (**str != '0')
		{
			if (!send_number(1, *str, file_name, mem))
				return (0);
			if (!send_number(3, *str, file_name, mem))
				return (0);
			(*str)++;
			(*len_s)--;
		}
		else
		{	
			(*str)++;
			(*len_s)--;
		}
	}
	return (1);
}

int	end_func(int *len_s, char **str, char *fname, char **mem)
{
	if (*len_s == 2)
	{
		if (**str != '0')
		{
			if (!send_number(2, *str, fname, mem))
				return (0);
			if (**str >= '2')
			{
				(*str)++;
				if (**str != '0')
					if (!send_number(1, *str, fname, mem))
						return (0);
			}
			return (1);
		}
		(*str)++;
		(*len_s)--;
	}
	if (*len_s == 1 && **str != '0')
		if (!send_number(1, *str, fname, mem))
			return (0);
	return (1);
}

int	number_func(int line_s, char *str, char *file_name, char **mem)
{
	if (!begin_func(&line_s, &str, file_name, mem))
		return (0);
	if (!end_func(&line_s, &str, file_name, mem))
		return (0);
	return (1);
}

int	control_func(char *arg, char *file_name, int len, char **mem)
{
	if (len % 3)
	{
		if (!number_func(len % 3, arg, file_name, mem))
			return (0);
		if (len / 3 > 0 && ft_atoi(arg, len % 3))
			if (!send_number(len - len % 3 + 1, arg, file_name, mem))
				return (0);
		arg += len % 3;
		len -= len % 3;
	}
	while (len > 0)
	{	
		if (!number_func(3, arg, file_name, mem))
			return (0);
		if (len == 0)
			break ;
		if (ft_atoi(arg, 3) && len > 3)
			if (!send_number(len - 2, arg, file_name, mem))
				return (0);
		len -= 3;
		arg += 3;
	}
	(*mem)--;
	**mem = '\n';
	return (1);
}

int	putnbr(char *arg, char *file_name, int len)
{
	char	*mem;
	char	*m1;
	char	*c;

	mem = malloc(2048);
	m1 = mem;
	c = mem;
	if (!control_func(arg, file_name, len, &m1))
	{
		free(c);
		return (0);
	}
	while (*mem != '\n')
	{
		write(1, mem, 1);
		mem++;
	}
	free(c);
	write(1, "\n", 1);
	return (1);
}
