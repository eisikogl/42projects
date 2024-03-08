/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utilis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 17:12:58 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/08 13:48:47 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	small_sort(t_stack *stack)
{
	if ((stack->size_a_ar + 1) == 2)
		two_sort(stack);
	if ((stack->size_a_ar + 1) == 3)
		three_sort(stack);
	if ((stack->size_a_ar + 1) == 4)
		four_sort(stack);
	if ((stack->size_a_ar + 1) == 5)
		five_sort(stack, min_indexing(stack));
}

int	check_order(t_stack *stack)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < stack->size_a_ar)
	{
		j = i + 1;
		while (j <= stack->size_a_ar)
		{
			if (stack->a[i] < stack->a[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
