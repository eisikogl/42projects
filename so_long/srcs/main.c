/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:38:28 by eisikogl          #+#    #+#             */
/*   Updated: 2022/08/11 01:26:20 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	start_init(t_gamedata *gamedata)
{
	gamedata->player_up_object = NULL;
	gamedata->player_left_object = NULL;
	gamedata->player_down_object = NULL;
	gamedata->player_right_object = NULL;
	gamedata->wall_object = NULL;
	gamedata->collectible_object = NULL;
	gamedata->exit_object = NULL;
	gamedata->direction_path = NULL;
	gamedata->mlx = NULL;
	gamedata->map = NULL;
	gamedata->mlx_window = NULL;
	gamedata->current_direction = 'S';
	gamedata->current_x = 0;
	gamedata->current_y = 0;
	gamedata->image_size = 0;
	gamedata->collectible_count = 0;
	gamedata->player_move_count = 0;
	gamedata->window_height = 0;
	gamedata->window_width = 0;
	gamedata->player_spawn_point_count = 0;
	gamedata->exit_count = 0;
	gamedata->collectible_size = 0;
}

void	game_init(t_gamedata *gamedata)
{
	void	*mlx_window;
	void	*mlx;

	ft_printf("Moves: %d \n", gamedata->player_move_count);
	mlx = mlx_init();
	gamedata->mlx = mlx;
	gamedata->window_width = 64 * l_size(gamedata);
	gamedata->window_height = 64 * l_count(gamedata);
	mlx_window = mlx_new_window(gamedata->mlx, gamedata->window_width, \
		gamedata->window_height, "Kitten grab`n trapp ");
	gamedata->mlx_window = mlx_window;
}

int	main(int argc, char **argv)
{
	t_gamedata	*gamedata;

	if (!(check_arg_extension(argc, argv)))
		return (0);
	gamedata = malloc(sizeof(t_gamedata));
	if (!gamedata)
		perror("Error\n");
	start_init(gamedata);
	gamedata->map_destination = argv[1];
	read_map(gamedata);
	map_validate(gamedata, l_size(gamedata) - 1, l_count(gamedata) - 1);
	validate(gamedata);
	game_init(gamedata);
	render_map(gamedata);
	mlx_hook(gamedata->mlx_window, 2, 1L << 0, key_event, gamedata);
	mlx_hook(gamedata->mlx_window, 17, 1L << 17, exit_game, gamedata);
	mlx_loop(gamedata->mlx);
}
