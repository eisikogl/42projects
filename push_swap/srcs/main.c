/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:17:09 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/08 16:00:16 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/push_swap.h"

int	main(int argc, char *argv[])
{
	t_stack	*stack;

	if (argc < 1)
		exit(1);
	stack = malloc(sizeof(t_stack));
	stack->arg_c = ft_argc(argc, argv, 1, 0);
	stack->a = (int *)malloc(sizeof(int) * stack->arg_c);
	stack->argumentoi = (int *)malloc(sizeof(int) * stack->arg_c);
	ft_argumentoi(argc, argv, stack, 1);
	ft_reversestack(stack);
	stack->b = (int *)malloc(sizeof(int) * stack->arg_c);
	stack->size_b = 0;
	stack->size_a_ar = stack->arg_c - 1;
	if (!check_order(stack))
	{
		if ((stack->size_a_ar + 1) <= 5)
			small_sort(stack);
		else
		{
			indexing(stack);
			big_sort(stack);
		}
	}
	free_me(stack);
}
