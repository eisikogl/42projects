/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_drawing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 06:08:23 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 19:58:54 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	image_get_pixel(t_gamedata *img, int x, int y)
{
	if (x < 0 || x > 64 || y < 0 || y > 64)
		return (0);
	if (img->ray_orientation == 'N')
		return (*((int *)(img->texture_addr[0] + (y * img->texture_length) \
		+ (x * 4))));
	else if (img->ray_orientation == 'S')
		return (*((int *)(img->texture_addr[1] + (y * img->texture_length) \
		+ (x * 4))));
	else if (img->ray_orientation == 'E')
		return (*((int *)(img->texture_addr[2] + (y * img->texture_length) \
		+ (x * 4))));
	else if (img->ray_orientation == 'W')
		return (*((int *)(img->texture_addr[3] + (y * img->texture_length) \
		+ (x * 4))));
	return (0);
}

void	drawline(t_gamedata *gamedata, int begx, int begy, int color)
{
	float	deltax;
	float	deltay;
	int		pixels;
	double	pixelx;
	double	pixely;

	deltax = gamedata->endx - begx;
	deltay = gamedata->endy - begy;
	pixels = sqrt((deltax * deltax) + (deltay * deltay));
	deltax /= pixels;
	deltay /= pixels;
	pixelx = begx;
	pixely = begy;
	while (pixels)
	{
		if (pixelx < gamedata->mapx * 16 && \
		pixely < gamedata->mapy * 16 && pixelx > 0 && pixely > 0)
		{
			my_mlx_pixel_put(gamedata, pixelx, pixely, color);
			pixelx += deltax;
			pixely += deltay;
		}
		--pixels;
	}
}

void	drawline3d_texture(t_gamedata *gamedata, float begx, \
float texture_x, float lineHeight)
{
	int		y;
	float	texture_step;
	float	texture_offset;
	float	walloffsety;
	float	texture_y;

	y = 0;
	texture_step = 64.0 / (float)lineHeight;
	texture_offset = 0;
	if (lineHeight > 512)
	{
		texture_offset = (lineHeight - 512) / 2.0;
		lineHeight = 512;
	}
	walloffsety = 256 - lineHeight / 2;
	texture_y = texture_offset * texture_step;
	while (y < lineHeight)
	{
		my_mlx_pixel_put3d(gamedata, -begx - 1, y + walloffsety, \
		image_get_pixel(gamedata, texture_x, texture_y));
		texture_y += texture_step;
		y++;
	}
}
