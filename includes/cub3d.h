/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:30:32 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/26 15:41:13 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define TILE_SIZE 100
# define WALL_COLOR 0xFF0000FF
# define MOVE_SPEED 5
# define KEY_ROT_SPEED 0.04
# define MOUSE_ROT_SPEED 0.02
# define MAP_X 5
# define MAP_Y 4
# define MAP_WALL_COLOR 0x000000FF
# define MAP_FLOOR_COLOR 0xFFFFFFFF
# define MAP_PLAYER_COLOR 0xFF0000FF
# define MAP_EMPTY_COLOR 0x0000000
# define TEX_WIDTH 64

enum	e_orientation
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
};

typedef struct s_2dvector
{
	int	x;
	int	y;
}	t_2dvector;

typedef struct s_2dvectorf
{
	double	x;
	double	y;
}	t_2dvectorf;

typedef struct s_player
{
	t_2dvector	pos;
	char		view;
}	t_player;

typedef struct s_data
{
	int						fd;
	char					*map_file_path;
	int						height;
	int						width;
	char					**map;
	t_player				player;
	char					*no_path;
	char					*ea_path;
	char					*so_path;
	char					*we_path;
	long int				ceil;
	long int				floor;
	int						flag_map;
	int						flag_complete;
}	t_data;

typedef struct s_player_mlx
{
	t_2dvector	pos;
	t_2dvectorf	dir;
	t_2dvectorf	plane;
}	t_player_mlx;

typedef struct s_mlx
{
	mlx_image_t		*render_img;
	mlx_image_t		*map_img;
	double			map_size;
	uint32_t		**img_arr[4];
	t_player_mlx	player;
	int				mouse_x;
}	t_mlx;

typedef struct s_render
{
	t_2dvector	map;
	t_2dvector	step;
	t_2dvectorf	player;
	t_2dvectorf	ray_dir;
	t_2dvectorf	side_dist;
	t_2dvectorf	delta_dist;
	int			hit;
	int			side;
	int			line_height;
	double		perp_wall_dist;
	int			draw_start;
	int			draw_end;
	int			tex_x;
	int			orientation;
}	t_render;

typedef struct s_cub3d
{
	double		time;
	void		*win;
	t_data		data;
	t_mlx		mlx;
	t_render	render;
}	t_cub3d;

// Functions

// Parser map

void			read_file(t_cub3d *cub3d, char *file_path);
int				fill_data(t_cub3d *cub3d, char *line);
void			fill_textures(t_cub3d *cub3d, char **line);
void			fill_colors(t_cub3d *cub3d, char **line);
void			fill_map(t_cub3d *cub3d, char *line, int i);

// Utils parser

void			init_parser_struct(t_data *data);
void			remove_newline(char *line);
int				ft_strlen_map(char *str);
char			*clean_spaces_str(char *str);
int				check_map_line(char *line);
int				check_required_data_for_map(t_cub3d *cub3d);
void			check_wall_map(t_cub3d *cub3d, char **map);
void			check_inside_map(t_cub3d *cub3d);
void			check_player(t_cub3d *cub3d, char **map);
int				check_all_data(t_cub3d *cub3d);
char			*prepare_line(t_cub3d *cub3d, char *str);
long int		read_colors(t_cub3d *cub3d, char **line);

// MLX

void			load_texture(t_cub3d *cub3d);

// MiniMap

void			init_minimap(t_cub3d *cub3d);
void			minimap(t_cub3d *cub3d);

// Render

void			render(t_cub3d *cub3d);
int				set_orientation(t_cub3d *cub3d);
void			draw_line(t_cub3d *cub3d, int x);

// Controls

void			on_key(mlx_key_data_t data, void *cub3d);
void			on_mouse_key(mouse_key_t button, action_t action,
					modifier_key_t mods, void *cub3d);
void			on_mouse_move(double x, double y, void *cub3d);
int				on_close(t_cub3d *cub3d);
void			on_frame(void *cub3d);

void			move_front(t_player_mlx *player, char **map);
void			move_right(t_player_mlx *player, char **map);
void			move_left(t_player_mlx *player, char **map);
void			move_back(t_player_mlx *player, char **map);
void			move_action(t_cub3d *cub3d);

void			cam_left(t_cub3d *cub3d, double rot_speed);
void			cam_right(t_cub3d *cub3d, double rot_speed);
void			cam_mouse(t_cub3d *cub3d, int x);

// Handle errors

void			ft_put_error(t_cub3d *cub3d, const char *err_msg, bool flag);

// Free

void			ft_free_parser(t_cub3d *cub3d);
void			ft_free_all(t_cub3d *cub3d);

#endif
