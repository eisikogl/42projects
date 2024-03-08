/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eisikogl <eisikogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:56:45 by eisikogl          #+#    #+#             */
/*   Updated: 2022/12/30 14:11:03 by eisikogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <math.h>
# include "../libs/mlx/mlx.h"
# include "../libs/Libft/libft.h"
# include "../includes/get_next_line.h"

# define PI 3.14159265359 
# define P2 1.5707963268
# define P3 4.71238898039
# define DGRE 0.0174533

typedef struct s_gamedata
{
	void		*mlx;
	void		*mlx_3dwindow;

	float		player_x;
	float		player_y;

	float		player_dy;
	float		player_dx;
	float		player_angle;

	int			mapx;
	int			mapy;
	char		**map;

	size_t		map_w;
	size_t		map_h;

	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;

	int			f_color[3];
	int			c_color[3];

	void		*img2d;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	void		*img3dwin;
	char		*addr3d;
	int			bits_per_pixel3d;
	int			line_length3d;
	int			endian3d;

	int			window_height;
	int			window_width;

	int			trgb_floor;
	int			trgb_ceiling;

	void		*texture_active_img[4];
	char		*texture_addr[4];
	int			texture_bits_per_pixel;
	int			texture_length;
	int			texture_endian;

	char		ray_orientation;

	char		starting_way;

	double		pos_x;
	double		pos_y;

	int			endx;
	int			endy;

}t_gamedata;

typedef struct s_raycaster
{
	float	ray_angle;
	float	ray_x;
	float	ray_y;
	int		depthoffield;

	float	x_offset;
	float	y_offset;

	float	disthori;
	float	horix;
	float	horiy;

	float	distverti;
	float	vertix;
	float	vertiy;

	float	distance;

}t_raycaster;

/*exit_func.c*/
int		free_exit_main(t_gamedata *gamedata);
int		ft_error(char *msg);
void	ft_free_cub(t_gamedata *cub);
int		exit_game(t_gamedata *gamedata);
/*init_func.c*/
void	init_textures(t_gamedata *gamedata);
void	init_2dwindow(t_gamedata *gamedata);
void	init_3dwindow(t_gamedata *gamedata);
void	init_floor_ceiling(t_gamedata *gamedata);
/*input_control_funcs.c*/
void	w_key(t_gamedata *gamedata);
void	a_key(t_gamedata *gamedata);
void	s_key(t_gamedata *gamedata);
void	d_key(t_gamedata *gamedata);
/*input_control.c*/
void	left_arrow_key(t_gamedata *gamedata);
void	right_arrow_key(t_gamedata *gamedata);
int		key_event(int key, t_gamedata *gamedata);
/*line_drawing.c*/
int		image_get_pixel(t_gamedata *img, int x, int y);
void	drawline(t_gamedata *gamedata, int begx, int begy, int color);
void	drawline3d_texture(t_gamedata *gamedata, float begx, \
float texture_x, float lineHeight);
/*main.c*/
int		init_main(t_gamedata *gamedata);
int		main(int argc, char **argv);
/*map_drawing.c*/
void	starting_pos(t_gamedata *gamedata, char orient);
void	render_call(t_gamedata *call_map);
void	ft_put_image(t_gamedata *call_map);
void	drawmap(t_gamedata *call_map, int y, int i);
void	drawmap2(t_gamedata *call_map);
/*map_utils.c*/
int		get_line_len(t_gamedata *call_map);
int		get_height(t_gamedata *call_map);
/*parse_map.c*/
int		ft_check_y_axis(t_gamedata *cub, size_t y, size_t x);
int		ft_check_x_axis(t_gamedata *cub, size_t y, size_t x);
int		ft_check_closed(t_gamedata *cub);
void	ft_resize_map(t_gamedata *cub);
/*parse.c*/
int		ft_check_valid_map_line(t_gamedata *cub, char *line);
int		ft_parse_map(t_gamedata *cub, char *line);
int		ft_check_resources(t_gamedata *cub);
int		ft_parse_line(char *line, t_gamedata *cub, int *num);
int		ft_parse_file(char *filename, t_gamedata *cub);
/*pixel_drawing.c*/
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_gamedata *gamedata, int x, int y, int color);
void	my_mlx_pixel_put3d(t_gamedata *gamedata, int x, int y, int color);
/*raycaster_functions.c*/
void	horizontalline(t_gamedata *gamedata, t_raycaster *caster);
void	find_pos_hoizont(t_gamedata *gamedata, t_raycaster *caster);
void	verticalline(t_gamedata *gamedata, t_raycaster *caster);
void	find_pos_vertical(t_gamedata *gamedata, t_raycaster *caster);
float	draw_2d_lines(t_gamedata *gamedata, t_raycaster *caster);
/*raycaster.c*/
float	dist(float beginx, float beginy, float endx, float endy);
void	get_rayangle(t_raycaster *caster);
void	draw_3d_lines(t_gamedata *gd, t_raycaster *rc, \
float shade, int ray_num);
void	get_current_angle(t_gamedata *gamedata, t_raycaster *caster);
void	drawrays(t_gamedata *gamedata);
/*rendering_functions.c*/
int		render_rect(t_gamedata *gamedata, int x, int y);
void	render_floor(t_gamedata *gamedata, int color);
void	render_ceiling(t_gamedata *gamedata, int color);
void	render_bg_map(t_gamedata *gamedata, int color);
void	pixelplayer(t_gamedata *gamedata);
/*utils.c*/
int		ft_max(int x, int y);
size_t	ft_splitlen(char **split);
void	ft_free_split(char **split);
int		ft_check_file_extension(char *name);
/*utils2.c*/
int		check_direction_path(t_gamedata *cub, char **split, int *num);
int		check_color_code(t_gamedata *cub, char **split, int *num);
int		is_valid_param(t_gamedata *cub, char *line, int *num);
#endif