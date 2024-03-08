/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_index_radix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 03:20:05 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/09 03:55:27 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/push_swap.h"

void	indexing(t_stack *stack)
{
	int	i;
	int	j;
	int	order_count;

	stack->index_arr = malloc(sizeof(int) * (stack->size_a_ar + 1));
	i = 0;
	while (i <= stack->size_a_ar)
	{
		j = 0;
		order_count = 0;
		while (j <= stack->size_a_ar)
		{
			if (j == i)
			{
				j++;
				continue ;
			}
			if (stack->a[i] > stack->a[j])
				order_count++;
			j++;
		}
		stack->index_arr[i] = order_count;
		i++;
	}
	indexing2(stack);
}

void	indexing2(t_stack *stack)
{
	int	i;

	i = 0;
	while (i <= stack->size_a_ar)
	{
		stack->a[i] = stack->index_arr[i];
		i++;
	}
	free(stack->index_arr);
	stack->index_arr = NULL;
}

void	big_sort(t_stack *stack)
{
	int	max_num;
	int	max_bits;
	int	i;
	int	size;

	i = 0;
	size = stack->size_a_ar + 1;
	max_num = size - 1;
	max_bits = 0;
	while ((max_num >> max_bits) != 0)
	{
		++max_bits;
	}
	while (i < max_bits)
	{
		bigsortfunction(stack, i, size);
		i++;
	}
}

void	bigsortfunction(t_stack *stack, int i, int size)
{	
	int	j;
	int	num;

	j = 0;
	while (j < size)
	{
		num = stack->a[stack->size_a_ar];
		if ((((num >> i) & 1) == 1))
		{
			f_ra(stack);
			ft_printf("ra\n");
		}
		else
		{
			f_pb(stack);
			ft_printf("pb\n");
		}
		j++;
	}
	while (stack->size_b != 0)
	{
		f_pa(stack);
		ft_printf("pa\n");
	}
}
