/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 20:01:17 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	get_line_len(t_gamedata *call_map)
{
	int	i;
	int	temp;
	int	j;

	i = 0;
	temp = 0;
	while (call_map->map[i] != NULL)
	{
		j = 0;
		while (call_map->map[i][j] != '\0')
		{
			j++;
		}
		if (j > temp)
		{
			temp = j;
		}
		i++;
	}
	return (temp);
}

int	get_height(t_gamedata *call_map)
{
	int	i;

	i = 0;
	while (call_map->map[i] != NULL)
	{
		i++;
	}
	return (i);
}
