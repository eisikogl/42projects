/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:31:15 by eisikogl          #+#    #+#             */
/*   Updated: 2022/10/15 22:55:30 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*threadhandler(void *philos)
{
	t_r	*rules;
	t_p	*phil;

	phil = (t_p *)philos;
	rules = phil->rule;
	if (phil->p_id % 2)
		usleep(15000);
	while (!(rules->dieded))
	{
		pthread_mutex_lock(&(rules->lock));
		if (rules->temp_eat)
		{
			pthread_mutex_unlock(&(rules->lock));
			break ;
		}
		pthread_mutex_unlock(&(rules->lock));
		eats(phil);
		print_philo(rules, phil->p_id, "is sleeping", 3);
		timing(rules->time_sleep, rules);
		print_philo(rules, phil->p_id, "is thinking", 4);
	}
	return (NULL);
}

void	eats(t_p *phil)
{
	t_r	*rules;

	rules = phil->rule;
	pthread_mutex_lock(&(rules->forks[phil->p_l_fork_id]));
	print_philo(rules, phil->p_id, "has taken a fork", 2);
	pthread_mutex_lock(&(rules->forks[phil->p_r_fork_id]));
	print_philo(rules, phil->p_id, "has taken a fork", 2);
	print_philo(rules, phil->p_id, "is eating", 1);
	timing(rules->time_eat, rules);
	pthread_mutex_lock(&(rules->meal_check));
	phil->last_eat = start_time();
	pthread_mutex_unlock(&(rules->meal_check));
	pthread_mutex_lock(&(rules->lock));
	phil->x_meal++;
	pthread_mutex_unlock(&(rules->lock));
	pthread_mutex_unlock(&(rules->forks[phil->p_l_fork_id]));
	pthread_mutex_unlock(&(rules->forks[phil->p_r_fork_id]));
}

int	create_thread(t_r *rule)
{
	int	i;
	t_p	*ph;

	i = 0;
	ph = rule->philo;
	pthread_mutex_lock(&(rule->lock));
	rule->first_time = start_time();
	pthread_mutex_unlock(&(rule->lock));
	while (i < rule->num_philo)
	{
		if (pthread_create(&(ph[i].thread_id), NULL, threadhandler, &(ph[i])))
			return (1);
		pthread_mutex_lock(&(rule->lock));
		ph[i].last_eat = start_time();
		pthread_mutex_unlock(&(rule->lock));
		i++;
	}
	check_death(rule, rule->philo);
	exit_thread(rule, ph);
	return (0);
}
