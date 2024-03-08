/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instantiate_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:39:28 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/29 03:48:21 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	instantiate_wall(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char	*path;

	path = "./assets/walls/wall2.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, path, \
		&gamedata->image_size, &gamedata->image_size);
	gamedata->wall_object = img;
	mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void	instantiate_collectible(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char	*path;

	path = "./assets/collectibles/collectible1.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, path, \
		&gamedata->image_size, &gamedata->image_size);
	gamedata->collectible_object = img;
	mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void	instantiate_exit(t_gamedata *gamedata, int x, int y)
{
	void	*img;
	char	*path;

	path = "./assets/exits/exit1.xpm";
	img = mlx_xpm_file_to_image(gamedata->mlx, path, \
		&gamedata->image_size, &gamedata->image_size);
	gamedata->exit_object = img;
	mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}

void	instantiate_player_direction(t_gamedata *gamedata, void *img)
{
	if (gamedata->current_direction == 'W')
		gamedata->player_up_object = img;
	if (gamedata->current_direction == 'A')
		gamedata->player_left_object = img;
	if (gamedata->current_direction == 'S')
		gamedata->player_down_object = img;
	if (gamedata->current_direction == 'D')
		gamedata->player_right_object = img;
}

void	instantiate_player(t_gamedata *gamedata, int x, int y)
{
	void	*img;

	img = mlx_xpm_file_to_image(gamedata->mlx, gamedata->direction_path, \
		&gamedata->image_size, &gamedata->image_size);
	instantiate_player_direction(gamedata, img);
	mlx_put_image_to_window(gamedata->mlx, gamedata->mlx_window, img, x, y);
}
