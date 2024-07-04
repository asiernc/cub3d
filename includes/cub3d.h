/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:30:32 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/04 16:06:20 by anovio-c         ###   ########.fr       */
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
	int			fd;
	int			height;
	int			witdh;
	char		**map;
	t_player	player;
	char		*no_path;
	char		*ea_path;
	char		*so_path;
	char		*we_path;
	int			ceil;
	int			floor;
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

void	ft_check_map(t_cub3d *cub3d, char *file_path);


// Handle errors
void	ft_put_error(const char *err_msg, bool flag);

#endif
