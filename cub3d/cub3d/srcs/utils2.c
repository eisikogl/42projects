/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/30 14:02:00 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	check_direction_path(t_gamedata *cub, char **split, int *num)
{
	char	*path;

	if (ft_splitlen(split) != 2)
		return (0);
	path = ft_strdup(split[1]);
	if (!ft_strncmp(split[0], "NO", 2) && !cub->no_path)
		cub->no_path = path;
	else if (!ft_strncmp(split[0], "SO", 2) && !cub->so_path)
		cub->so_path = path;
	else if (!ft_strncmp(split[0], "WE", 2) && !cub->we_path)
		cub->we_path = path;
	else if (!ft_strncmp(split[0], "EA", 2) && !cub->ea_path)
		cub->ea_path = path;
	else
		return (0);
	*num += 1;
	return (1);
}

int	check_color_code(t_gamedata *cub, char **split, int *num)
{
	char	**colors;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (ft_splitlen(split) != 2)
		return (0);
	colors = ft_split(split[1], ',');
	if (ft_splitlen(colors) != 3)
		n = -1;
	while (i < 3 && n != -1)
	{
		n = ft_atoi(colors[i]);
		if ((n < 0) | (n > 255))
			n = -1;
		else if (!ft_strncmp(split[0], "F", 1))
			cub->f_color[i] = n;
		else if (!ft_strncmp(split[0], "C", 1))
			cub->c_color[i] = n;
		i++;
	}
	ft_free_split(colors);
	*num += 1;
	return (n != -1);
}

int	is_valid_param(t_gamedata *cub, char *line, int *num)
{
	int		r;
	char	*first;
	size_t	l;
	char	**split;

	split = ft_split(line, ' ');
	first = split[0];
	l = ft_strlen(first);
	r = 0;
	if (!ft_strncmp(first, "NO", l) || !ft_strncmp(first, "SO", l)
		|| !ft_strncmp(first, "WE", l) || !ft_strncmp(first, "EA", l))
	{
		r = check_direction_path(cub, split, num);
	}
	else if (!ft_strncmp(first, "F", l) || !ft_strncmp(first, "C", l))
		r = check_color_code(cub, split, num);
	if (r != 0)
		free(line);
	ft_free_split(split);
	return (r);
}
