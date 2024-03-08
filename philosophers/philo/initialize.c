/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:30:58 by eisikogl          #+#    #+#             */
/*   Updated: 2022/10/15 19:14:48 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_rules(t_r *rule, char **argv)
{
	rule->num_philo = ft_atoi(argv[1]);
	rule->time_death = ft_atoi(argv[2]);
	rule->time_eat = ft_atoi(argv[3]);
	rule->time_sleep = ft_atoi(argv[4]);
	rule->temp_eat = 0;
	if (rule->num_philo < 1 || rule->time_death < 60 || rule->time_eat < 60 \
	|| rule->time_sleep < 60 || rule->num_philo > 200)
		return (1);
	if (argv[5])
		rule->arg = ft_atoi(argv[5]);
	else
		rule->arg = -1;
	return (0);
}

int	mutex_init(t_r *rule)
{
	int	i;

	i = rule->num_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(rule->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rule->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(rule->meal_check), NULL))
		return (1);
	if (pthread_mutex_init(&(rule->lock), NULL))
		return (1);
	return (0);
}

void	philo_init(t_r *rule)
{
	int	i;

	i = rule->num_philo;
	while (--i >= 0)
	{
		rule->philo[i].p_id = i;
		rule->philo[i].p_l_fork_id = i;
		rule->philo[i].p_r_fork_id = (i + 1) % rule->num_philo;
		rule->philo[i].rule = rule;
		rule->philo[i].last_eat = 0;
		rule->philo[i].x_meal = 0;
	}
}
