/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 13:54:37 by eisikogl          #+#    #+#             */
/*   Updated: 2022/01/12 16:28:30 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*ps1;
	char	*ps2;

	ps1 = (char *)s1;
	ps2 = (char *)s2;
	i = 0;
	if (!s1 && !s2)
		return (0);
	while (i < n)
	{
		if (ps1[i] != ps2[i])
		{
			return ((unsigned char)ps1[i] - (unsigned char)ps2[i]);
		}	
		i++;
	}
	return (0);
}
