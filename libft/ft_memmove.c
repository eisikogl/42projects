/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:30:35 by eisikogl          #+#    #+#             */
/*   Updated: 2022/02/25 16:04:53 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*psrc;
	char	*pdst;
	size_t	i;

	i = 0;
	pdst = dst;
	psrc = (char *)src;
	if (!dst && !src)
		return (NULL);
	if (src < dst)
	{
		while (len--)
		{
			pdst[len] = psrc[len];
		}
	}
	else
	{
		while (len--)
		{
			pdst[i] = psrc[i];
			i++;
		}
	}
	return (pdst);
}
