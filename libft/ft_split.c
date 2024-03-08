/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <42istanbul.com.tr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:36:34 by eisikogl          #+#    #+#             */
/*   Updated: 2022/02/25 16:36:44 by eisikogl         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_count_strings(char const *s, char c)
{
	int		newstr;
	size_t	str_n;

	newstr = 0;
	str_n = 0;
	while (*s)
	{
		if (*s != c && newstr == 0)
		{
			newstr = 1;
			str_n++;
		}
		else if (*s == c)
			newstr = 0;
		s++;
	}
	return (str_n);
}

size_t	ft_count_chr(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

void	ft_free_tab(char **tab, size_t n)
{
	if (!tab[n])
	{
		while (n > 0)
			free(tab[n--]);
		free(tab);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	str_n;
	size_t	n;
	size_t	len;

	if (!s)
		return (0);
	str_n = ft_count_strings(s, c);
	split = (char **)malloc(sizeof(char *) * (str_n + 1));
	if (!split)
		return (0);
	n = 0;
	while (n < str_n)
	{
		while (*s == c)
			s++;
		len = ft_count_chr(s, c);
		split[n] = (char *)malloc(sizeof(char) * (len + 1));
		ft_free_tab(split, n);
		ft_strlcpy(split[n], (char *)s, len + 1);
		s = s + len;
		n++;
	}
	split[str_n] = 0;
	return (split);
}
