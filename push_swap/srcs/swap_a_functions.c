/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_functions_a.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:14:09 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/06 06:32:39 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/push_swap.h"

void	f_sa(t_stack *stack)
{
	int	temp;

	if (stack->size_a_ar < 1)
		return ;
	temp = stack->a[stack->size_a_ar];
	stack->a[stack->size_a_ar] = stack->a[stack->size_a_ar - 1];
	stack->a[stack->size_a_ar - 1] = temp;
}

void	f_pa(t_stack *stack)
{
	stack->a[stack->size_a_ar + 1] = stack->b[stack->size_b - 1];
	stack->size_a_ar++;
	stack->size_b--;
}

void	f_ra(t_stack *stack)
{
	int	temp;
	int	i;
	int	j;

	i = stack->size_a_ar;
	j = 1;
	temp = stack->a[stack->size_a_ar];
	while (i > 0)
	{
		stack->a[i] = stack->a[stack->size_a_ar - j];
		i--;
		j++;
	}
	stack->a[0] = temp;
}

void	f_rra(t_stack *stack)
{
	int	temp;
	int	i;
	int	j;

	i = 0;
	j = 0;
	temp = stack->a[0];
	while (i < stack->size_a_ar)
	{
		stack->a[0 + j] = stack->a[j + 1];
		i++;
		j++;
	}
	stack->a[stack->size_a_ar] = temp;
}
