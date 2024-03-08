/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:55:50 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/29 19:37:01 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	ft_check_valid_map_line(t_gamedata *cub, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10 NSEW", line[i]))
		{
			printf("MAP ERROR: %c is not a valid char\n", line[i]);
			return (0);
		}
		else if (ft_strchr("NSEW", line[i]) && cub->starting_way != 0)
		{
			printf("MAP ERROR: Only one starting point valid.\n");
			return (0);
		}
		else if (ft_strchr("NSEW", line[i]) && cub->starting_way == 0)
		{
			cub->starting_way = line[i];
			cub->pos_x = (double)i;
			cub->pos_y = (double)cub->map_h;
		}
		i++;
	}
	return (1);
}

int	ft_parse_map(t_gamedata *cub, char *line)
{
	int		i;
	size_t	w;
	char	**new_map;

	i = -1;
	if (!ft_check_valid_map_line(cub, line))
		return (0);
	w = ft_strlen(line);
	cub->map_h++;
	if (w > cub->map_w)
		cub->map_w = w;
	new_map = ft_calloc(cub->map_h + 1, sizeof(char *));
	while (cub->map[++i])
	{
		new_map[i] = cub->map[i];
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(cub->map);
	cub->map = new_map;
	return (1);
}

int	ft_check_resources(t_gamedata *cub)
{
	int	i;

	i = 0;
	if (cub->no_path == NULL || cub->so_path == NULL
		|| cub->we_path == NULL || cub->ea_path == NULL )
	{
		printf("Error in paths\n");
		return (0);
	}
	while (i < 3)
	{
		if (cub->f_color[i] == 256 || cub->c_color[i] == 256)
		{
			printf("Error in colors\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_parse_line(char *line, t_gamedata *cub, int *num)
{
	int	ret;

	if (ft_strlen(line) <= 1)
	{
		ret = *num != -1;
		if (ret != 0)
			free(line);
	}
	else if (*num < 6 && *num != -1)
		ret = is_valid_param(cub, line, num);
	else
	{
		*num = -1;
		if (!ft_check_resources(cub))
			return (0);
		ret = ft_parse_map(cub, line);
	}
	if (ret == 0)
		printf("Error\n");
	return (ret);
}

int	ft_parse_file(char *filename, t_gamedata *cub)
{
	int		fd;
	int		num;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_error("Map not Found"));
	line = get_next_line(fd);
	num = 0;
	while (line)
	{
		if (!ft_parse_line(line, cub, &num))
		{
			free(line);
			return (0);
		}
		line = get_next_line(fd);
	}
	close(fd);
	free(line);
	if (!cub->starting_way)
		return (ft_error("No starting way\n"));
	ft_resize_map(cub);
	return (ft_check_closed(cub));
}
