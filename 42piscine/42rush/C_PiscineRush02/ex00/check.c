#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "check.h"
#include "func.h"
#include "numbers.h"

int	ft_atoi(char *str, int n)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (i < n)
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	return (nb);
}

int	is_alpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	ft_strcmp(char *s1, char *s2, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s2[i] == ':' || s2[i] <= ' ')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && !(str[i] < '0' || str[i] > '9'))
		i++;
	return (i);
}
