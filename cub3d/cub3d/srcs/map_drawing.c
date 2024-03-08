/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:42:20 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 19:46:47 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	starting_pos(t_gamedata *gamedata, char orient)
{
	if (orient == 'N')
		gamedata->player_angle = PI / 2;
	else if (orient == 'S')
		gamedata->player_angle = P3;
	else if (orient == 'E')
		gamedata->player_angle = 0;
	else if (orient == 'W')
		gamedata->player_angle = PI;
	gamedata->player_dx = cos(gamedata->player_angle) * 5;
	gamedata->player_dy = sin(gamedata->player_angle) * 5;
	pixelplayer(gamedata);
}

void	render_call(t_gamedata *call_map)
{
	render_floor(call_map, call_map->trgb_floor);
	render_ceiling(call_map, call_map->trgb_ceiling);
	render_bg_map(call_map, call_map->trgb_floor);
}

void	ft_put_image(t_gamedata *call_map)
{
	mlx_put_image_to_window(call_map->mlx, call_map->mlx_3dwindow, \
	call_map->img2d, 0, 0);
	mlx_put_image_to_window(call_map->mlx, call_map->mlx_3dwindow, \
	call_map->img3dwin, call_map->mapx * 16, 0);
}

void	drawmap(t_gamedata *call_map, int y, int i)
{
	int		j;
	int		x;

	render_call(call_map);
	while (call_map->map[++i] != NULL)
	{
		j = -1;
		x = 0;
		while (call_map->map[i][++j] != '\0')
		{
			if (call_map->map[i][j] == '1')
				render_rect(call_map, x, y);
			if (ft_strchr("NSEW", call_map->map[i][j]))
			{
				call_map->player_x = x;
				call_map->player_y = y;
				starting_pos(call_map, call_map->map[i][j]);
			}
			x += 16;
		}
		y += 16;
	}
	ft_put_image(call_map);
}

void	drawmap2(t_gamedata *call_map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	y = 0;
	i = -1;
	call_map->img2d = mlx_new_image(call_map->mlx, \
	call_map->mapx * 16, call_map->window_height);
	call_map->img3dwin = mlx_new_image(call_map->mlx, 1024, 512);
	render_call(call_map);
	while (call_map->map[++i] != NULL)
	{
		j = -1;
		x = 0;
		while (call_map->map[i][++j] != '\0')
		{
			if (call_map->map[i][j] == '1')
				render_rect(call_map, x, y);
			x += 16;
		}
		y += 16;
	}
	pixelplayer(call_map);
	ft_put_image(call_map);
}
