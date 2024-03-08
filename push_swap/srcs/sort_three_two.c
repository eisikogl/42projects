/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:23:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/08 13:49:54 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/push_swap.h"

void	two_sort(t_stack *stack)
{
	if (stack->a[1] > stack->a[0])
	{
		f_sa(stack);
		ft_printf("sa\n");
	}
}

void	three_sort(t_stack *stack)
{
	int	i;

	i = stack->size_a_ar;
	if (stack->a[i] < stack->a[0] && stack->a[i] < stack->a[i - 1] && \
	stack->a[i - 1] > stack->a[0])
	{
		f_sa(stack);
		f_ra(stack);
		ft_printf("sa\nra\n");
	}
	if (stack->a[i] < stack->a[i - 1] && stack->a[i] > stack->a[0] && \
	stack->a[i - 1] > stack->a[0])
	{
		f_rra(stack);
		ft_printf("rra\n");
	}
	three_sort2(stack, i);
}

void	three_sort2(t_stack *stack, int i)
{
	if (stack->a[i] > stack->a[i - 1] && stack->a[i] < stack->a[0] && \
	stack->a[i - 1] < stack->a[0])
	{
		f_sa(stack);
		ft_printf("sa\n");
	}
	if (stack->a[i] > stack->a[i - 1] && stack->a[i] > stack->a[0] && \
	stack->a[i - 1] < stack->a[0])
	{
		f_ra(stack);
		ft_printf("ra\n");
	}
	if (stack->a[i] > stack->a[i - 1] && stack->a[i] > stack->a[0] && \
	stack->a[i - 1] > stack->a[0])
	{
		f_sa(stack);
		f_rra(stack);
		ft_printf("sa\nrra\n");
	}
}
