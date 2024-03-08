/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 17:08:29 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_max(int x, int y)
{
	if (x >= y)
		return (x);
	return (y);
}

size_t	ft_splitlen(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

int	ft_check_file_extension(char *name)
{
	char	**split;
	int		i;

	split = ft_split(name, '.');
	i = 0;
	while (split[i])
		i++;
	if (i <= 1)
	{
		ft_free_split(split);
		printf("Error in file format \n");
		return (0);
	}
	if (ft_strncmp(split[i - 1], "cub", ft_max(3, ft_strlen(split[i - 1]))))
	{
		ft_free_split(split);
		printf("Error in file format \n");
		return (0);
	}
	ft_free_split(split);
	return (1);
}
