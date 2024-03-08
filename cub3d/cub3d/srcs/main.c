/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:42:20 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/30 13:49:37 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	init_main(t_gamedata *gamedata)
{
	gamedata->map = ft_calloc(1, sizeof(char *));
	if (!gamedata->map)
		return (0);
	gamedata->map_h = 0;
	gamedata->map_w = 0;
	gamedata->map[0] = NULL;
	gamedata->mlx = mlx_init();
	return (1);
}

int	main(int argc, char **argv)
{
	t_gamedata	*gamedata;

	if (argc != 2)
		printf("add map \n");
	gamedata = malloc(sizeof(t_gamedata));
	if (!gamedata)
		return (0);
	if (!init_main(gamedata))
		return (free_exit_main(gamedata));
	if (!ft_check_file_extension(argv[1]) || !ft_parse_file(argv[1], gamedata))
	{
		ft_free_cub(gamedata);
		return (free_exit_main(gamedata));
	}
	init_2dwindow(gamedata);
	init_3dwindow(gamedata);
	init_textures(gamedata);
	init_floor_ceiling(gamedata);
	drawmap(gamedata, 0, -1);
	mlx_hook(gamedata->mlx_3dwindow, 2, 1L << 0, key_event, gamedata);
	mlx_hook(gamedata->mlx_3dwindow, 17, 1L << 17, exit_game, gamedata);
	mlx_loop(gamedata->mlx);
	return (0);
}
