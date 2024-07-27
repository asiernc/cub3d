/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:57:44 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/27 18:26:53 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libs/libft/libft.h"

static int	get_color(t_cub3d *cub3d, int map_x, int map_y, mlx_image_t *img)
{
	int	x;
	int	y;

	x = map_x / ((img->width + 0.0) / cub3d->data.width);
	y = map_y / ((img->height + 0.0) / cub3d->data.height);
	if (cub3d->data.map[y][x] == '1')
		return (MAP_WALL_COLOR);
	if (cub3d->data.map[y][x] == '0')
		return (MAP_FLOOR_COLOR);
	return (MAP_EMPTY_COLOR);
}

static void	draw_map(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (int)cub3d->mlx.map_img->height)
	{
		x = -1;
		while (++x < (int)cub3d->mlx.map_img->width)
			mlx_put_pixel(cub3d->mlx.map_img, x, y,
				get_color(cub3d, x, y, cub3d->mlx.map_img));
	}
}

static void	draw_player(t_cub3d *cub3d)
{
	int		player[2];
	int		x;
	int		y;

	player[0] = ((cub3d->mlx.player.pos.y + 0.0) / TILE_SIZE)
		* cub3d->mlx.map_size;
	player[1] = ((cub3d->mlx.player.pos.x + 0.0) / TILE_SIZE)
		* cub3d->mlx.map_size;
	y = player[0] - cub3d->mlx.map_size / 4;
	while (++y < player[0] + cub3d->mlx.map_size / 4)
	{
		x = player[1] - cub3d->mlx.map_size / 4;
		while (++x < player[1] + cub3d->mlx.map_size / 4)
			mlx_put_pixel(cub3d->mlx.map_img, x, y, MAP_PLAYER_COLOR);
	}
}

void	minimap(t_cub3d *cub3d)
{
	cub3d->mlx.map_img = mlx_new_image(cub3d->win, cub3d->mlx.map_size * cub3d->data.width,
			cub3d->mlx.map_size * cub3d->data.height);
	if (!cub3d->mlx.map_img)
		ft_put_error(cub3d, "MLX new image", false);
	draw_map(cub3d);
	draw_player(cub3d);
	if (mlx_image_to_window(cub3d->win, cub3d->mlx.map_img, 0, 0) < 0)
		ft_put_error(cub3d, "MLX image to win", false);
}

void	init_minimap(t_cub3d *cub3d)
{
	double	size_x;
	double	size_y;

	size_x = (WIDTH + 0.0) / MAP_X / cub3d->data.width;
	size_y = (HEIGHT + 0.0) / MAP_Y / cub3d->data.height;
	if (size_x < size_y)
		cub3d->mlx.map_size = size_x;
	else
		cub3d->mlx.map_size = size_y;
	cub3d->mlx.map_img = NULL;
}
