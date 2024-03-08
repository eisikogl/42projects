/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 22:39:02 by eisikogl          #+#    #+#             */
/*   Updated: 2022/07/29 03:50:04 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	move_character_up(t_gamedata *gamedata)
{
	gamedata->current_direction = 'W';
	player_movement(gamedata, gamedata->current_x - 1, gamedata->current_y);
}

void	move_character_left(t_gamedata *gamedata)
{
	gamedata->current_direction = 'A';
	player_movement(gamedata, gamedata->current_x, gamedata->current_y - 1);
}

void	move_character_down(t_gamedata *gamedata)
{
	gamedata->current_direction = 'S';
	player_movement(gamedata, gamedata->current_x + 1, gamedata->current_y);
}

void	move_character_right(t_gamedata *gamedata)
{
	gamedata->current_direction = 'D';
	player_movement(gamedata, gamedata->current_x, gamedata->current_y + 1);
}

void	player_movement(t_gamedata *gamedata, int current_x, int current_y)
{
	if (gamedata->map[current_x][current_y] != '1' && \
		gamedata->map[current_x][current_y] != 'E')
	{
		if (gamedata->map[current_x][current_y] == 'C' && \
			gamedata->collectible_size != gamedata->collectible_count)
			gamedata->collectible_count += 1;
		gamedata->map[gamedata->current_x][gamedata->current_y] = '0';
		gamedata->current_x = current_x;
		gamedata->current_y = current_y;
		gamedata->map[current_x][current_y] = 'P';
		gamedata->player_move_count += 1;
		ft_printf("Moves: %d \n", gamedata->player_move_count);
		render_map(gamedata);
	}
	else if (gamedata->collectible_size == gamedata->collectible_count && \
		gamedata->map[current_x][current_y] == 'E')
	{
		gamedata->player_move_count += 1;
		ft_printf("Moves: %d \n", gamedata->player_move_count);
		exit_game(gamedata, 2);
	}
}
