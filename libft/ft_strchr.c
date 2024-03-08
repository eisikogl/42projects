/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 10:02:07 by eisikogl          #+#    #+#             */
/*   Updated: 2022/02/25 16:06:16 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ps;
	int		i;

	i = 0;
	ps = (char *)s;
	while (ps[i])
	{
		if (ps[i] == (char)c)
		{
			return (ps + i);
		}
		i++;
	}
	if (c == '\0')
		return (&ps[i]);
	return (NULL);
}
