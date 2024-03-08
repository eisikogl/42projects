/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:20:07 by calion            #+#    #+#             */
/*   Updated: 2022/12/29 20:29:41 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

float	dist(float beginx, float beginy, float endx, float endy)
{
	float	deltax;
	float	deltay;

	deltax = endx - beginx;
	deltay = endy - beginy;
	return (sqrt((deltax * deltax) + (deltay * deltay)));
}

void	get_rayangle(t_raycaster *caster)
{
	if (caster->ray_angle < 0)
	{
		caster->ray_angle += 2 * PI;
	}
	if (caster->ray_angle > 2 * PI)
	{
		caster->ray_angle -= 2 * PI;
	}
}

void	draw_3d_lines(t_gamedata *gd, t_raycaster *rc, float shade, int ray_num)
{
	float	texture_x;

	if (shade == 1.0)
	{
		texture_x = (int)(rc->ray_x * 2.0) % 64;
		gd->ray_orientation = 'N';
		if (rc->ray_angle > PI)
		{
			texture_x = 63 - texture_x;
			gd->ray_orientation = 'S';
		}
	}
	else
	{
		texture_x = (int)(rc->ray_y * 2.0) % 64;
		gd->ray_orientation = 'E';
		if (rc->ray_angle > P2 && rc->ray_angle < P3)
		{
			texture_x = 63 - texture_x;
			gd->ray_orientation = 'W';
		}
	}
	drawline3d_texture(gd, ray_num / 2, texture_x, (16 * 512) / rc->distance);
}

void	get_current_angle(t_gamedata *gamedata, t_raycaster *caster)
{
	float	current_angle;

	current_angle = gamedata->player_angle - caster->ray_angle;
	if (current_angle < 0)
		current_angle += 2 * PI;
	if (current_angle > 2 * PI)
		current_angle -= 2 * PI;
	caster->distance = caster->distance * cos(current_angle);
}

void	drawrays(t_gamedata *gamedata)
{
	t_raycaster	caster;
	int			ray_num;
	float		shade;

	mlx_clear_window(gamedata->mlx, gamedata->mlx_3dwindow);
	ray_num = 0;
	caster.ray_angle = gamedata->player_angle - DGRE * 30;
	get_rayangle(&caster);
	while (ray_num < 2048)
	{
		caster.disthori = 1000000;
		caster.depthoffield = 0;
		horizontalline(gamedata, &caster);
		find_pos_hoizont(gamedata, &caster);
		caster.distverti = 1000000;
		caster.depthoffield = 0;
		verticalline(gamedata, &caster);
		find_pos_vertical(gamedata, &caster);
		shade = draw_2d_lines(gamedata, &caster);
		get_current_angle(gamedata, &caster);
		draw_3d_lines(gamedata, &caster, shade, ray_num);
		caster.ray_angle += DGRE / 34;
		get_rayangle(&caster);
		ray_num++;
	}
}
