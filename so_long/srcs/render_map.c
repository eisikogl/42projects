/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:38:38 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/29 03:51:46 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	get_object_path(t_gamedata *gamedata)
{
	char	*path;

	if (gamedata->current_direction == 'W')
		path = "./assets/player/player_up.xpm";
	if (gamedata->current_direction == 'A')
		path = "./assets/player/player_left.xpm";
	if (gamedata->current_direction == 'S')
		path = "./assets/player/player_down.xpm";
	if (gamedata->current_direction == 'D')
		path = "./assets/player/player_right.xpm";
	gamedata->direction_path = path;
}

void	instantiate_world(t_gamedata *gamedata, int x, int y, char object)
{
	if (object == '1')
		instantiate_wall(gamedata, x, y);
	if (object == 'P')
	{
		get_object_path(gamedata);
		instantiate_player(gamedata, x, y);
	}
	if (object == 'C')
		instantiate_collectible(gamedata, x, y);
	if (object == 'E')
		instantiate_exit(gamedata, x, y);
}

void	render_map(t_gamedata *gamedata)
{
	int	i;
	int	j;
	int	x;
	int	y;

	mlx_clear_window(gamedata->mlx, gamedata->mlx_window);
	i = 0;
	x = 0;
	y = 0;
	while (gamedata -> map[i])
	{
		j = 0;
		x = 0;
		while (gamedata -> map[i][j])
		{
			instantiate_world(gamedata, x, y, gamedata -> map[i][j]);
			x += 64;
			j++;
		}
		y += 64;
		i++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
