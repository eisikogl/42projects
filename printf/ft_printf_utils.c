/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:18:19 by eisikogl          #+#    #+#             */
/*   Updated: 2022/04/03 13:18:21 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_number(int number, int *count)
{
	if (number == -2147483648)
	{
		ft_put_str("-2147483648", count);
		return ;
	}
	if (number < 0)
	{
		ft_put_char('-', count);
		number = -number;
	}
	if (number >= 10)
	{
		ft_put_number(number / 10, count);
		number = number % 10;
	}
	if (number < 10)
		ft_put_char(number + 48, count);
}

void	ft_put_number_unsigned_integer(unsigned int number, int *count)
{
	int				temp;
	unsigned int	maxvalue;

	maxvalue = 4294967295;
	if (number < 0)
	{
		number *= -1;
		temp = maxvalue - number;
		ft_put_number_unsigned_integer(temp, count);
	}
	else
	{
		if (number >= 10)
		{
			ft_put_number_unsigned_integer(number / 10, count);
			number = number % 10;
		}
		if (number < 10)
			ft_put_char(number + 48, count);
	}
}

void	ft_put_hex(unsigned long long number, int *count, char sign)
{
	int				temp;
	unsigned int	maxvalue;

	maxvalue = 4294967295;
	if (number < 0)
	{
		number *= -1;
		temp = maxvalue - number;
		ft_put_hex(temp, count, sign);
	}
	else
	{
		if (number >= 16)
		{
			ft_put_hex(number / 16, count, sign);
			number = number % 16;
		}
		if (number >= 10 && sign == 'X')
			ft_put_char(number + 55, count);
		else if (number >= 10 && sign == 'x')
			ft_put_char(number + 87, count);
		else if (number <= 9)
			ft_put_char(number + 48, count);
	}
}

void	ft_put_pointer(void *ptr, int *count)
{
	ft_put_str("0x", count);
	ft_put_hex((unsigned long long)ptr, count, 'x');
}
