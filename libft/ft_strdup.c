/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 12:44:47 by eisikogl          #+#    #+#             */
/*   Updated: 2022/02/25 16:05:34 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	char	*p2;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	p = (char *)malloc(len + 1);
	if (p == NULL)
		return (NULL);
	p2 = p;
	while (s1[i])
	{
		p2[i] = s1[i];
		i++;
	}
	p2[i] = '\0';
	return (p2);
}
