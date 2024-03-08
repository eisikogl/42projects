/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:59:14 by eisikogl          #+#    #+#             */
/*   Updated: 2022/06/12 17:59:16 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	*g_decode_this;

void	ft_itoa(pid_t pid)
{
	char	c;

	if (pid >= 10)
		ft_itoa(pid / 10);
	c = (pid % 10) + 48;
	write(1, &c, 1);
}

int	ft_pow(int i, int n)
{
	int	power;

	power = 1;
	while (n != 0)
	{
		power = power * i;
		n--;
	}
	return (power);
}

char	decoder(int *get_char)
{
	int	i;
	int	n;
	int	sum;

	sum = 0;
	n = 7;
	i = 0;
	while (i < 8)
	{	
		sum += (get_char[i] * ft_pow(2, n));
		n--;
		i++;
	}
	return ((char)sum);
}

void	get_char(int signum)
{
	static int	i = 0;
	char		c;

	if (signum == SIGUSR1)
		g_decode_this[i++] = 1;
	else if (signum == SIGUSR2)
		g_decode_this[i++] = 0;
	if (i == 8)
	{
		c = decoder(g_decode_this);
		write(1, &c, 1);
		i = 0;
	}
}

int	main(void)
{
	write(1, "Server Pid: ", 13);
	ft_itoa(getpid());
	write(1, "\n", 1);
	g_decode_this = malloc(sizeof(*g_decode_this) * 8);
	while (1)
	{
		signal(SIGUSR1, get_char);
		signal(SIGUSR2, get_char);
		pause();
	}
	free(g_decode_this);
}
