/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:30:32 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/15 13:03:28 by molasz-a         ###   ########.fr       */
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
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1280
# define HEIGHT 720
# define MAP_X 5
# define MAP_Y 4
# define MAP_WALL_COLOR 0x000000FF
# define MAP_FLOOR_COLOR 0xFFFFFFFF
# define MAP_PLAYER_COLOR 0xFF0000FF

typedef struct s_player
{
	int		x;
	int		y;
	char	view;
}	t_player;

typedef struct s_data
{
	int				fd;
	char			*map_file_path;
	int				height;
	int				width;
	char			**map;
	t_player		player;
	char			*no_path;
	char			*ea_path;
	char			*so_path;
	char			*we_path;
	unsigned int	ceil;
	unsigned int	floor;
}	t_data;

typedef struct s_mlx
{
	double		map_tile;
	mlx_image_t	*map_img;
	mlx_image_t	no_img;
	mlx_image_t	ea_img;
	mlx_image_t	so_img;
	mlx_image_t	we_img;
}	t_mlx;

typedef struct s_cub3d
{
	void	*win;
	t_data	data;
	t_mlx	mlx;

}	t_cub3d;


// Functions

// Parser map

void			read_file(t_cub3d *cub3d, char *file_path);
void			get_height_width(t_cub3d *cub3d, char *file_path);
int				fill_data(t_cub3d *cub3d, char *line);
void			fill_textures(t_cub3d *cub3d, char **line);
void			fill_colors(t_cub3d *cub3d, char **line);
void			fill_map(t_cub3d *cub3d, char *line, int y);

// Utils parser

void			remove_newline(char *line);
char			*clean_spaces_str(char *str);
int				check_map_line(char *line);
int				check_required_data_for_map(t_cub3d *cub3d);
void			check_wall_map(t_cub3d *cub3d);
void			check_inside_map(t_cub3d *cub3d);
void			check_player(t_cub3d *cub3d);
int				check_all_data(t_cub3d *cub3d);
void			test_print(t_data *data);

// Color utils

unsigned int	read_colors(char **line);
unsigned int	rgb_to_int(int red, int green, int blue);

// Controls

void			on_key(mlx_key_data_t data, void *cub3d);
int				on_close(t_cub3d *cub3d);

void			move_front(t_cub3d *cub3d);
void			move_right(t_cub3d *cub3d);
void			move_back(t_cub3d *cub3d);
void			move_left(t_cub3d *cub3d);
void			move_action(t_cub3d *cub3d);

void			cam_left(t_cub3d *cub3d);
void			cam_right(t_cub3d *cub3d);


// Handle errors
void			ft_put_error(const char *err_msg, bool flag);

// Free
void			ft_free_all(t_cub3d *cub3d);

// MiniMap
void	minimap(t_cub3d *cub3d);

#endif
