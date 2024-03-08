/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:31:02 by eisikogl          #+#    #+#             */
/*   Updated: 2022/10/15 22:21:08 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_color(int color)
{
	if (color == 1)
		red();
	if (color == 2)
		blue();
	if (color == 3)
		yellow();
	if (color == 4)
		green();
	if (color == 5)
		purple();
}

int	ft_atoi(char *str)
{
	int		neg;
	long	num;
	int		i;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			neg *= -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

long long	start_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

long long	calculate_time(long long past, long long pres)
{
	return (pres - past);
}

void	timing(long long time, t_r *rule)
{
	long long	t;

	t = start_time();
	while (1)
	{
		pthread_mutex_lock(&(rule->lock));
		if (rule->dieded)
		{
			pthread_mutex_unlock(&(rule->lock));
			break ;
		}
		pthread_mutex_unlock(&(rule->lock));
		if (calculate_time(t, start_time()) >= time)
			break ;
		usleep(150);
	}
}
