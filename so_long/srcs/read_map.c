/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:39:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/11 01:26:09 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	l_count(t_gamedata *gamedata)
{
	char	c;
	int		line_count;
	int		fd;

	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata, 0);
	line_count = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			line_count++;
	}
	close(fd);
	return (line_count + 1);
}

int	l_size(t_gamedata *gamedata)
{
	char	c;
	int		line_size;
	int		fd;

	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata, 0);
	line_size = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		line_size++;
	}
	close(fd);
	return (line_size);
}

int	get_file_length(t_gamedata *gamedata)
{
	char	c;
	int		i;
	int		fd;

	i = 0;
	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata, 0);
	while (read(fd, &c, 1))
	{
		i++;
	}
	close(fd);
	return (i);
}

void	get_initial_informations(t_gamedata *gamedata)
{
	int	i;
	int	j;

	i = 0;
	while (gamedata->map[i])
	{
		j = 0;
		while (gamedata->map[i][j])
		{
			if (gamedata->map[i][j] == 'P')
			{
				gamedata->player_spawn_point_count += 1;
				gamedata->current_x = i;
				gamedata->current_y = j;
			}
			if (gamedata->map[i][j] == 'C')
				gamedata->collectible_size += 1;
			if (gamedata->map[i][j] == 'E')
				gamedata->exit_count += 1;
			j++;
		}
		i++;
	}
}

void	read_map(t_gamedata *gamedata)
{
	int		fd;
	int		file_length;
	char	*map;

	file_length = get_file_length(gamedata);
	map = (char *)malloc(file_length + 1);
	if (!map)
		exit_game(gamedata, 0);
	fd = open(gamedata->map_destination, O_RDONLY);
	if (fd < 0)
		exit_game(gamedata, 0);
	read(fd, map, file_length);
	gamedata->map = ft_split(map, '\n');
	get_initial_informations(gamedata);
	close(fd);
	free(map);
}
