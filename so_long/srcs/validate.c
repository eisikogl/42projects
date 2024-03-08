/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:39:13 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/29 09:48:53 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	map_validate(t_gamedata *gamedata, int row_size, int column_size)
{
	int	i;
	int	j;

	i = 0;
	while (gamedata->map[i])
	{
		j = 0;
		while (gamedata->map[i][j])
		{
			if (i == column_size && gamedata->map[i][j] != '1')
				exit_game(gamedata, 13);
			if (j == row_size && gamedata->map[i][j] != '1')
				exit_game(gamedata, 15);
			norminette_validate(gamedata, i, j);
			j++;
		}
		if (row_size != j - 1)
			exit_game(gamedata, 8);
		i++;
	}
	if (column_size != i - 1)
		exit_game(gamedata, 9);
}

void	norminette_validate(t_gamedata *gamedata, int i, int j)
{
	if (i == 0 && gamedata->map[i][j] != '1')
		exit_game(gamedata, 12);
	if (j == 0 && gamedata->map[i][j] != '1')
		exit_game(gamedata, 14);
	if (gamedata->map[i][j] != '0' && gamedata->map[i][j] != '1' && \
		gamedata->map[i][j] != 'P' && gamedata->map[i][j] != 'E' && \
		gamedata->map[i][j] != 'C')
		exit_game(gamedata, 7);
}

void	validate(t_gamedata *gamedata)
{
	if (gamedata->player_spawn_point_count > 1)
		exit_game(gamedata, 4);
	if (gamedata->player_spawn_point_count < 1)
		exit_game(gamedata, 10);
	if (gamedata->collectible_size < 1)
		exit_game(gamedata, 5);
	if (gamedata->exit_count < 1)
		exit_game(gamedata, 6);
}

int	check_arg_extension(int argc, char **argv)
{
	int	map_arglen;

	if (argc < 2)
	{
		ft_printf("Error\nInvalid Arg: Map file missing");
		return (0);
	}
	if (argc > 2)
	{
		ft_printf("Error\nInvalid Arg: Too many Arguments");
		return (0);
	}
	map_arglen = ft_strlen(argv[1]);
	if (!(ft_strnstr(&argv[1][map_arglen - 4], ".ber", 4)))
	{
		perror("Error\ninvalid Map extension use .ber");
		return (0);
	}
	return (1);
}
