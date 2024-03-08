/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_b_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 06:28:14 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/08 08:20:23 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/push_swap.h"

void	f_sb(t_stack *stack)
{
	int	temp;

	if (stack->size_b <= 1)
		return ;
	temp = stack->b[stack->size_b - 1];
	stack->b[stack->size_b - 1] = stack->b[stack->size_b - 2];
	stack->b[stack->size_b - 2] = temp;
}

void	f_pb(t_stack *stack)
{
	stack->size_b++;
	stack->b[stack->size_b - 1] = stack->a[stack->size_a_ar];
	stack->size_a_ar--;
}

void	f_rb(t_stack *stack)
{
	int	temp;
	int	i;
	int	j;

	i = stack->size_b - 1;
	j = 1;
	temp = stack->b[stack->size_b - 1];
	while (i > 0)
	{
		stack->b[i] = stack->b[stack->size_b - 1 - j];
		i--;
		j++;
	}
	stack->b[0] = temp;
}

void	f_rrb(t_stack *stack)
{
	int	temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	temp = stack->b[0];
	while (i < stack->size_b - 1)
	{
		stack->b[0 + j] = stack->b[j + 1];
		i++;
		j++;
	}
	stack->b[stack->size_b - 1] = temp;
}
