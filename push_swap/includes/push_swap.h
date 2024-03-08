/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:14:09 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/09 03:55:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <stdlib.h>
# include "../libarys/ft_printf/ft_printf.h"
# include "../libarys/libft/libft.h"

typedef struct s_stack
{
	int	*a;
	int	*b;
	int	arg_c;
	int	size_b;
	int	size_a_ar;
	int	*index_arr;
	int	*argumentoi;
}	t_stack;

long	ft_argc(int argc, char **str, int i, int j);
void	ft_argumentoi(int argc, char **str, t_stack *stack, int i);
int		ft_argumentoi2(char **str, int i, int j);
void	ft_reversestack(t_stack *stack);

int		ft_argerror(char **str, int i, int j);
void	doubles_check(t_stack *stack);
void	free_me_error(t_stack *stack);
void	free_me(t_stack *stack);
void	ft_error(char *err, int i);

void	small_sort(t_stack *stack);
int		check_order(t_stack *stack);

int		min_indexing(t_stack *stack);
void	four_sort(t_stack *stack);
void	five_sort(t_stack *stack, int min_index);
void	five_sort2(t_stack *stack);

void	indexing(t_stack *stack);
void	indexing2(t_stack *stack);
void	big_sort(t_stack *stack);
void	bigsortfunction(t_stack *stack, int i, int size);

void	two_sort(t_stack *stack);
void	three_sort(t_stack *stack);
void	three_sort2(t_stack *stack, int i);

void	f_sa(t_stack *stack);
void	f_sb(t_stack *stack);
void	f_ss(t_stack *stack);
void	f_pa(t_stack *stack);
void	f_pb(t_stack *stack);
void	f_ra(t_stack *stack);
void	f_rb(t_stack *stack);
void	f_rr(t_stack *stack);
void	f_rra(t_stack *stack);
void	f_rrb(t_stack *stack);
void	f_rrr(t_stack *stack);

#endif
