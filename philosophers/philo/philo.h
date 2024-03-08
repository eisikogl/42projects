/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:30:51 by eisikogl          #+#    #+#             */
/*   Updated: 2022/10/15 19:15:46 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_p
{
	int			p_id;
	int			p_l_fork_id;
	int			p_r_fork_id;
	long long	last_eat;
	int			x_meal;
	struct s_r	*rule;
	pthread_t	thread_id;
}	t_p;

typedef struct s_r
{
	int				num_philo;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				dieded;
	long long		first_time;
	int				temp_eat;
	int				arg;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	meal_check;
	pthread_mutex_t	writing;
	pthread_mutex_t	lock;
	t_p				philo[250];
}	t_r;

/*threads.c*/
void		*threadhandler(void *philos);
void		eats(t_p *phil);
int			create_thread(t_r *rule);

/*utils.c*/
void		pick_color(int color);
int			ft_atoi(char *str);
long long	start_time(void);
long long	calculate_time(long long past, long long pres);
void		timing(long long time, t_r *rule);

/*error_maneger.c*/
int			is_all_num(char *argv);
int			write_error(char *str);
int			error_manager(int error);

/*errorhandling.c*/
void		errorhandler(int exit_mode);
int			errorcheck(int argc, char **argv);
int			errorcheck_two(int argc, char **argv);

/*Initialize.c*/
int			init_rules(t_r *rule, char **argv);
int			mutex_init(t_r *rule);
void		philo_init(t_r *rule);

/*main.c*/
void		print_philo(t_r *rules, int id, char *string, int color);
void		check_death_two(t_p *phil, t_r *r);
void		check_death(t_r *r, t_p *phil);
void		exit_thread(t_r *rule, t_p *phil);
int			main(int argc, char **argv);

/*Colorcoding*/

void		red(void);
void		yellow(void);
void		green(void);
void		blue(void);
void		purple(void);
void		reset(void);

#endif