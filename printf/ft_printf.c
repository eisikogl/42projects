/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:18:37 by eisikogl          #+#    #+#             */
/*   Updated: 2022/04/03 13:18:40 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_char(char c, int *count)
{
	*count += write(1, &c, 1);
}

void	ft_put_str(char *str, int *count)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		*count += write(1, "(null)", 6);
		return ;
	}
	while (str[i])
	{
		ft_put_char(str[i], count);
		i++;
	}
}

void	ft_check_sign(va_list ap, const char *str, int i, int *count)
{
	if (str[i] == 'c')
		ft_put_char((char)va_arg(ap, int), count);
	if (str[i] == 's')
		ft_put_str(va_arg(ap, char *), count);
	if (str[i] == 'p')
		ft_put_pointer(va_arg(ap, void *), count);
	if (str[i] == 'd' || str[i] == 'i')
		ft_put_number(va_arg(ap, int), count);
	if (str[i] == 'u')
		ft_put_number_unsigned_integer(va_arg(ap, unsigned int), count);
	if (str[i] == 'x' || str[i] == 'X')
		ft_put_hex(va_arg(ap, unsigned int), count, str[i]);
	if (str[i] == '%')
		ft_put_char('%', count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	int		i;
	va_list	ap;

	va_start(ap, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			ft_check_sign(ap, str, i, &count);
		}
		else
			ft_put_char(str[i], &count);
		i++;
	}
	va_end(ap);
	return (count);
}
