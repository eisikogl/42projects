/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:36:40 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/28 22:45:38 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (dest[j] && j < n)
		j++;
	while ((src[k]) && ((j + k + 1) < n))
	{
		dest[j + k] = src[k];
		k++;
	}
	if (j != n)
		dest[j + k] = '\0';
	return (j + ft_strlen(src));
}
