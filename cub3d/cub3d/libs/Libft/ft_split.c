/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:48:06 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/30 13:48:27 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	fletter;
	int	i;
	int	count;

	fletter = -1;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (fletter == -1 && s[i] != c)
			fletter = i;
		else if (fletter != -1 && s[i] == c)
		{
			fletter = -1;
			count++;
		}
		i++;
	}
	if (fletter != -1)
		count++;
	return (count);
}

static char	*get_word(char *s, char c, int *i)
{
	int		count;
	int		j;
	char	*sol;

	count = 0;
	j = 0;
	while (s[count] && s[count] != c)
	{
		count++;
	}
	*i = *i + count;
	sol = (char *)malloc(count + 1);
	if (!(sol))
		return (NULL);
	while (j < count)
	{
		sol[j] = s[j];
		j++;
	}
	sol[j] = 0;
	return (sol);
}

char	**ft_split(char const *s, char c)
{
	char	**sol;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	sol = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!(sol))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			sol[j++] = get_word((char *)&s[i], c, &i);
		else
			i++;
	}
	sol[j] = NULL;
	return (sol);
}
