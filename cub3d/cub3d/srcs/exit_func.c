/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/30 14:36:23 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	free_exit_main(t_gamedata *gamedata)
{
	free(gamedata->mlx);
	free(gamedata->map);
	free(gamedata);
	return (0);
}

int	ft_error(char *msg)
{
	printf("%s\n", msg);
	return (0);
}

void	ft_free_cub(t_gamedata *cub)
{
	free(cub->no_path);
	free(cub->so_path);
	free(cub->we_path);
	free(cub->ea_path);
}

int	exit_game(t_gamedata *gamedata)
{
	if (gamedata->mlx_3dwindow != NULL)
		mlx_destroy_window(gamedata->mlx, gamedata->mlx_3dwindow);
	ft_free_cub(gamedata);
	exit(1);
	return (0);
}
