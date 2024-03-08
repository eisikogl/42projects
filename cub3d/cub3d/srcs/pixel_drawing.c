/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_drawing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:42:20 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 18:11:18 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../includes/cube3d.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_gamedata *gamedata, int x, int y, int color)
{
	char	*dst;

	dst = gamedata->addr + (y * gamedata->line_length \
			+ x * (gamedata->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_pixel_put3d(t_gamedata *gamedata, int x, int y, int color)
{
	char	*dst3d;

	dst3d = gamedata->addr3d + (y * gamedata->line_length3d \
			+ x * (gamedata->bits_per_pixel3d / 8));
	*(unsigned int *)dst3d = color;
}
