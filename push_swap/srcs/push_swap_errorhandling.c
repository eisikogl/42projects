/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_errorhandling.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 00:16:15 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/08 12:50:57 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/push_swap.h"

int	ft_argerror(char **str, int i, int j)
{
	int		neg;
	long	num;

	neg = 1;
	num = 0;
	if (str[i][j] == '-' || str[i][j] == '+')
	{
		if (!ft_isdigit(str[i][j + 1]))
			ft_error("Error\n", 1);
		if (str[i][j] == '-')
			neg *= -1;
		j++;
	}
	if (!ft_isdigit(str[i][j]))
		ft_error("Error\n", 1);
	while ((str[i][j] >= '0' && str[i][j] <= '9'))
	{
		num = num * 10 + (str[i][j] - 48);
		if (num > 0x7FFFFFFF && neg == 1)
			ft_error("Error\n", 1);
		if (num > 0x80000000 && neg == -1)
			ft_error("Error\n", 1);
		j++;
	}
	return (j);
}

void	doubles_check(t_stack *stack)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack->arg_c)
	{
		j = i + 1;
		while (j <= stack->arg_c - 1)
		{
			if (stack->a[i] == stack->a[j])
				free_me_error(stack);
			j++;
		}
		i++;
	}
}

void	ft_error(char *err, int i)
{
	if (err != 0)
		ft_putstr_fd(err, 2);
	exit(i);
}

void	free_me_error(t_stack *stack)
{
	if (stack->a)
		free(stack->a);
	if (stack->b)
		free(stack->b);
	if (stack)
		free(stack);
	ft_error("Error\n", 1);
}

void	free_me(t_stack *stack)
{
	if (stack->a)
		free(stack->a);
	if (stack->b)
		free(stack->b);
	if (stack)
		free(stack);
}
