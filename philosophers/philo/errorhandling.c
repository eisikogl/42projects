/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorhandling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 02:33:21 by eisikogl          #+#    #+#             */
/*   Updated: 2022/10/15 21:02:41 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	reset(void)
{
	printf("\033[0m");
}

void	errorhandler(int exit_mode)
{
	if (exit_mode == 1)
		printf("Wrong number of Arguments\n");
	if (exit_mode == 2)
		printf("There has to be atleast one Philosopher\n");
	if (exit_mode == 3)
		printf("Time to die has to be greater than 60ms\n");
	if (exit_mode == 4)
		printf("Time eating has to be greater than 60ms\n");
	if (exit_mode == 5)
		printf("Time sleeping has to be greater than 60ms\n");
	if (exit_mode == 6)
		printf("Times every philo eats has to be greater than 0\n");
	if (exit_mode == 7)
		printf("Input only Numbers\n");
}

int	errorcheck(int argc, char **argv)
{
	if ((argc != 5) && (argc != 6))
	{
		errorhandler(1);
		return (1);
	}
	if (is_all_num(argv[1]) || is_all_num(argv[2]) || \
	is_all_num(argv[3]) || is_all_num(argv[4]))
	{
		errorhandler(7);
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		errorhandler(2);
		return (1);
	}
	if (ft_atoi(argv[2]) < 60)
	{
		errorhandler(3);
		return (1);
	}
	if (errorcheck_two(argc, argv))
		return (1);
	return (0);
}

int	errorcheck_two(int argc, char **argv)
{
	if (ft_atoi(argv[3]) < 60)
	{
		errorhandler(4);
		return (1);
	}
	if (ft_atoi(argv[4]) < 60)
	{
		errorhandler(5);
		return (1);
	}
	if (argv[5])
	{
		if (is_all_num(argv[5]))
		{
			errorhandler(7);
			return (1);
		}
		if (ft_atoi(argv[5]) < 1)
		{
			errorhandler(6);
			return (1);
		}
	}
	return (0);
}
