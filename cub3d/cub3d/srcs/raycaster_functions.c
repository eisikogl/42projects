/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:20:07 by calion            #+#    #+#             */
/*   Updated: 2022/12/29 19:58:32 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	horizontalline(t_gamedata *gamedata, t_raycaster *caster)
{
	float	atan;

	atan = tan(caster->ray_angle);
	if (caster->ray_angle < PI)
	{
		caster->ray_y = ((int)(gamedata->player_y / 16) * 16) - 0.0001;
		caster->ray_x = ((gamedata->player_y - caster->ray_y) / atan) \
		+ gamedata->player_x;
		caster->y_offset = -16;
		caster->x_offset = -(caster->y_offset / atan);
	}
	if (caster->ray_angle > PI)
	{
		caster->ray_y = ((int)(gamedata->player_y / 16) * 16) + 16;
		caster->ray_x = ((gamedata->player_y - caster->ray_y) / atan) \
		+ gamedata->player_x;
		caster->y_offset = 16;
		caster->x_offset = -(caster->y_offset / atan);
	}
	if (caster->ray_angle == 0 || caster->ray_angle == PI)
	{
		caster->ray_x = gamedata->player_x;
		caster->ray_y = gamedata->player_y;
		caster->depthoffield = gamedata->mapy;
	}
}

void	find_pos_hoizont(t_gamedata *gamedata, t_raycaster *caster)
{
	int	map_x;
	int	map_y;

	caster->horix = gamedata->player_x;
	caster->horiy = gamedata->player_y;
	while (caster->depthoffield < gamedata->mapy)
	{
		map_x = ((int)(caster->ray_x) / 16);
		map_y = ((int)(caster->ray_y) / 16);
		if (map_x < gamedata->mapx && map_y < gamedata->mapy && \
		map_x >= 0 && map_y >= 0 && gamedata->map[map_y][map_x] == '1')
		{
			caster->horix = caster->ray_x;
			caster->horiy = caster->ray_y;
			caster->disthori = dist(gamedata->player_x, gamedata->player_y, \
			caster->horix, caster->horiy);
			caster->depthoffield = gamedata->mapy;
		}
		else
		{
			caster->ray_x += caster->x_offset;
			caster->ray_y += caster->y_offset;
			caster->depthoffield += 1;
		}
	}
}

void	verticalline(t_gamedata *gamedata, t_raycaster *caster)
{
	float	ntan;

	ntan = tan(caster->ray_angle);
	if (caster->ray_angle > P2 && caster->ray_angle < P3)
	{
		caster->ray_x = (((int)gamedata->player_x / 16) * 16) - 0.0001;
		caster->ray_y = (gamedata->player_x - caster->ray_x) * ntan \
		+ gamedata->player_y;
		caster->x_offset = -16;
		caster->y_offset = -caster->x_offset * ntan;
	}
	if (caster->ray_angle < P2 || caster->ray_angle > P3)
	{
		caster->ray_x = (((int)gamedata->player_x / 16) * 16) + 16;
		caster->ray_y = (gamedata->player_x - caster->ray_x) * ntan \
		+ gamedata->player_y;
		caster->x_offset = 16;
		caster->y_offset = -caster->x_offset * ntan;
	}
	if (caster->ray_angle == 0 || caster->ray_angle == PI)
	{
		caster->ray_x = gamedata->player_x;
		caster->ray_y = gamedata->player_y;
		caster->depthoffield = gamedata->mapx;
	}
}

void	find_pos_vertical(t_gamedata *gamedata, t_raycaster *caster)
{
	int	map_x;
	int	map_y;

	caster->vertix = gamedata->player_x;
	caster->vertiy = gamedata->player_y;
	while (caster->depthoffield < gamedata->mapx)
	{
		map_x = (int)(caster->ray_x) / 16;
		map_y = (int)(caster->ray_y) / 16;
		if (map_x < gamedata->mapx && map_y < gamedata->mapy && map_x >= 0 && \
		map_y >= 0 && gamedata->map[map_y][map_x] == '1')
		{
			caster->vertix = caster->ray_x;
			caster->vertiy = caster->ray_y;
			caster->distverti = dist(gamedata->player_x, gamedata->player_y, \
			caster->vertix, caster->vertiy);
			caster->depthoffield = gamedata->mapx;
		}
		else
		{
			caster->ray_x += caster->x_offset;
			caster->ray_y += caster->y_offset;
			caster->depthoffield += 1;
		}
	}
}

float	draw_2d_lines(t_gamedata *gamedata, t_raycaster *caster)
{
	float	shade;

	shade = 1;
	if (caster->distverti < caster->disthori)
	{
		caster->ray_x = caster->vertix;
		caster->ray_y = caster->vertiy;
		caster->distance = caster->distverti;
		shade = 0.5;
	}
	if (caster->disthori < caster->distverti)
	{
		caster->ray_x = caster->horix;
		caster->ray_y = caster->horiy;
		caster->distance = caster->disthori;
		shade = 1;
	}
	gamedata->endx = caster->ray_x;
	gamedata->endy = caster->ray_y;
	drawline(gamedata, gamedata->player_x + 2, gamedata->player_y + 2, \
	0x0000FF00);
	return (shade);
}
