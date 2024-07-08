/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:30:32 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/05 12:33:47 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

# define WIDTH 1920
# define HEIGHT 1080

# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define ESCAPE 53

typedef struct s_player
{
	int		x;
	int		y;
	char	view;
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
	unsigned int			ceil;
	unsigned int			floor;
}	t_data;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_cub3d
{
	void	*mlx;
	void	*win;
	t_data	data;

}	t_cub3d;


// Functions

// Parser map

void			read_file(t_cub3d *cub3d, char *file_path);
void			get_height_width(t_cub3d *cub3d, char *file_path);
int				fill_data(t_cub3d *cub3d, char *line);
void			fill_textures(t_cub3d *cub3d, char **line);
void			fill_colors(t_cub3d *cub3d, char **line);
void			fill_map(t_cub3d *cub3d, char *line);

// Utils parser

void			remove_newline(char *line);
char			*clean_spaces_str(char *str);
int				check_map_line(char *line);
int				check_required_data_for_map(t_cub3d *cub3d);
void			check_wall_map(t_cub3d *cub3d);
void			check_player(t_cub3d *cub3d);
int				check_all_data(t_cub3d *cub3d);
void			test_print(t_data *data);

// Color utils

unsigned int	read_colors(char **line);
unsigned int	rgb_to_int(int red, int green, int blue);

// Handle errors
void			ft_put_error(const char *err_msg, bool flag);

#endif
