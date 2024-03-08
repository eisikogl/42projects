/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:41:30 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/08 12:17:02 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

long	ft_argc(int argc, char **str, int i, int j)
{
	int		len;
	int		arcount;

	arcount = 0;
	while (i < argc)
	{
		len = ft_strlen(str[i]);
		while (str[i][j] == 32 || (str[i][j] >= 9 && str[i][j] <= 13))
			j++;
		if (j == len)
		{
			i++;
			j = 0;
			continue ;
		}
		j = ft_argerror(str, i, j);
		arcount++;
		if (j != len)
			continue ;
		j = 0;
		i++;
	}
	return (arcount);
}

void	ft_argumentoi(int argc, char **str, t_stack *stack, int i)
{
	int		len;
	int		j;
	int		z;

	z = 0;
	j = 0;
	while (i < argc)
	{
		len = ft_strlen(str[i]);
		while (str[i][j] == 32 || (str[i][j] >= 9 && str[i][j] <= 13))
			j++;
		if (j == len)
		{	
			i++;
			j = 0;
			continue ;
		}
		stack->argumentoi[z++] = ft_argumentoi2(str, i, j);
		j = ft_argerror(str, i, j);
		if (j != len)
			continue ;
		j = 0;
		i++;
	}
}

int	ft_argumentoi2(char **str, int i, int j)
{
	int		neg;
	long	num;

	neg = 1;
	num = 0;
	if (str[i][j] == '-' || str[i][j] == '+')
	{
		if (str[i][j] == '-')
		{
			neg *= -1;
		}
		j++;
	}
	while ((str[i][j] >= '0' && str[i][j] <= '9'))
	{
		num = num * 10 + (str[i][j] - 48);
		j++;
	}
	return (num * neg);
}

void	ft_reversestack(t_stack *stack)
{
	int	i;
	int	j;

	i = 0;
	j = stack->arg_c - 1;
	while (i < stack->arg_c)
	{
		stack->a[i] = stack->argumentoi[j];
		i++;
		j--;
	}
	free(stack->argumentoi);
	doubles_check(stack);
}

// void	ft_argumentoi(int argc, char **str, t_stack *stack)
// {
// 	int		neg;
// 	long	num;
// 	int		len;
// 	int		i;
// 	int		j;
// 	int		z;

// 	stack->a = (int *)malloc(sizeof(int) * stack->arg_c);
// 	stack->argumentoi = (int *)malloc(sizeof(int) * stack->arg_c);
// 	i = 1;
// 	z = 0;
// 	j = 0;
// 	while (i < argc)
// 	{
// 		len = ft_strlen(str[i]);
// 		neg = 1;
// 		num = 0;
// 		while (str[i][j] == 32 || (str[i][j] >= 9 && str[i][j] <= 13))
// 			j++;
// 		if (j == len)
// 		{	
// 			i++;
// 			j = 0;
// 			continue ;
// 		}
// 		if (str[i][j] == '-' || str[i][j] == '+')
// 		{
// 			if (str[i][j] == '-')
// 			{
// 				neg *= -1;
// 			}
// 			j++;
// 		}
// 		while ((str[i][j] >= '0' && str[i][j] <= '9'))
// 		{
// 			num = num * 10 + (str[i][j] - 48);
// 			j++;
// 		}
// 		stack->argumentoi[z] = (num * neg);
// 		z++;
// 		if (j != len)
// 			continue ;
// 		j = 0;
// 		i++;
// 	}
// }