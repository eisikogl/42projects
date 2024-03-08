/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ab_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 06:30:56 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/06 06:34:27 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	f_ss(t_stack *stack)
{
	f_sa(stack);
	f_sb(stack);
}

void	f_rr(t_stack *stack)
{
	f_ra(stack);
	f_rb(stack);
}

void	f_rrr(t_stack *stack)
{
	f_rra(stack);
	f_rrb(stack);
}
