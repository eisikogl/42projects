/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:18:51 by eisikogl          #+#    #+#             */
/*   Updated: 2022/04/03 13:18:56 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_check_sign(va_list ap, const char *str, int i, int *count);

void	ft_put_char(char c, int *count);
void	ft_put_str(char *str, int *count);
void	ft_put_number(int number, int *count);
void	ft_put_number_unsigned_integer(unsigned int number, int *count);
void	ft_put_hex(unsigned long long number, int *count, char sign);
void	ft_put_pointer(void *ptr, int *count);

#endif
