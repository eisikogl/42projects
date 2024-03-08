/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:54:13 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/28 22:45:04 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*sr;
	char	*dst;
	size_t	i;

	i = 0;
	dst = dest;
	sr = (char *)src;
	if (!dest && !src)
		return (NULL);
	if (src < dest)
	{
		while (len--)
		{
			dst[len] = sr[len];
		}
	}
	else
	{
		while (len--)
		{
			dst[i] = sr[i];
			i++;
		}
	}
	return (dst);
}
