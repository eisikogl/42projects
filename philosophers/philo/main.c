/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:31:15 by eisikogl          #+#    #+#             */
/*   Updated: 2022/10/15 23:21:48 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo(t_r *rules, int id, char *string, int color)
{
	pthread_mutex_lock(&(rules->writing));
	if (!(rules->dieded) && !(rules->temp_eat))
	{	
		printf("%lldms ", calculate_time(rules->first_time, start_time()));
		pick_color(color);
		printf(" %i ", id + 1);
		printf("%s\n", string);
		reset();
	}
	pthread_mutex_unlock(&(rules->writing));
}

void	check_death_two(t_p *phil, t_r *r)
{
	int	i;

	i = -1;
	while (++i < r->num_philo)
	{
		pthread_mutex_lock(&(r->meal_check));
		if (calculate_time(phil[i].last_eat, start_time()) >= r->time_death)
		{
			pthread_mutex_lock(&(r->lock));
			print_philo(r, i, "is dead", 5);
			r->dieded = 1;
			pthread_mutex_unlock(&(r->lock));
			pthread_mutex_unlock(&(r->meal_check));
			break ;
		}
		pthread_mutex_unlock(&(r->meal_check));
		usleep(10);
	}
	return ;
}

void	check_death(t_r *r, t_p *phil)
{
	int	i;

	while (!(r->temp_eat))
	{
		check_death_two(phil, r);
		pthread_mutex_lock(&(r->lock));
		if (r->dieded)
		{
			pthread_mutex_unlock(&(r->lock));
			break ;
		}
		pthread_mutex_unlock(&(r->lock));
		i = 0;
		pthread_mutex_lock(&(r->lock));
		while (i < r->num_philo && phil[i].x_meal >= r->arg && r->arg != -1)
			i++;
		if (r->num_philo == i)
			r->temp_eat = 1;
		pthread_mutex_unlock(&(r->lock));
	}
}

void	exit_thread(t_r *rule, t_p *phil)
{
	int	i;

	i = -1;
	while (++i < rule->num_philo)
	{
		if (rule->num_philo == 1)
			break ;
		pthread_join(phil[i].thread_id, NULL);
	}
	i = -1;
	while (++i < rule->num_philo)
		pthread_mutex_destroy(&(rule->forks[i]));
	pthread_mutex_destroy(&(rule->writing));
	pthread_mutex_destroy(&(rule->lock));
}

int	main(int argc, char **argv)
{
	t_r	*rule;

	if (!errorcheck(argc, argv))
	{
		rule = malloc(sizeof(t_r));
		if (init_rules(rule, argv))
			return (error_manager(1));
		if (mutex_init(rule))
			return (error_manager(2));
		philo_init(rule);
		if (create_thread(rule))
			return (write_error("There was an error creating the threads"));
	}
	return (0);
}
