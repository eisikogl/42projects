/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/30 13:57:10 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	left_arrow_key(t_gamedata *gamedata)
{
	gamedata->player_angle += PI / 50;
	if (gamedata->player_angle > 2 * PI)
	{
		gamedata->player_angle -= 2 * PI;
	}
	gamedata->player_dx = cos(gamedata->player_angle) * 5;
	gamedata->player_dy = sin(gamedata->player_angle) * 5;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawmap2(gamedata);
}

void	right_arrow_key(t_gamedata *gamedata)
{
	gamedata->player_angle -= PI / 50;
	if (gamedata->player_angle < 0)
	{
		gamedata->player_angle += 2 * PI;
	}
	gamedata->player_dx = cos(gamedata->player_angle) * 5;
	gamedata->player_dy = sin(gamedata->player_angle) * 5;
	mlx_destroy_image(gamedata->mlx, gamedata->img2d);
	mlx_destroy_image(gamedata->mlx, gamedata->img3dwin);
	drawmap2(gamedata);
}

int	key_event(int key, t_gamedata *gamedata)
{
	if (key == 13)
		w_key(gamedata);
	if (key == 0)
		a_key(gamedata);
	if (key == 1)
		s_key(gamedata);
	if (key == 2)
		d_key(gamedata);
	if (key == 123)
		left_arrow_key(gamedata);
	if (key == 124)
		right_arrow_key(gamedata);
	if (key == 53)
	{
		exit_game(gamedata);
	}
	return (0);
}
