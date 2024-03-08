/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 19:25:13 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	w_key(t_gamedata *gamedata)
{
	gamedata->player_y -= gamedata->player_dy;
	gamedata->player_x += gamedata->player_dx;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawmap2(gamedata);
}

void	a_key(t_gamedata *gamedata)
{
	gamedata->player_x -= cos(gamedata->player_angle - PI / 2) * 5;
	gamedata->player_y += sin(gamedata->player_angle - PI / 2) * 5;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawmap2(gamedata);
}

void	s_key(t_gamedata *gamedata)
{
	gamedata->player_y += gamedata->player_dy;
	gamedata->player_x -= gamedata->player_dx;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawmap2(gamedata);
}

void	d_key(t_gamedata *gamedata)
{
	gamedata->player_x += cos(gamedata->player_angle - PI / 2) * 5;
	gamedata->player_y -= sin(gamedata->player_angle - PI / 2) * 5;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawmap2(gamedata);
}
