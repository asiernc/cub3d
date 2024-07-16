/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:57:44 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/16 15:07:30 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libs/libft/libft.h"

static double	get_size(t_cub3d *cub3d)
{
	double	size_x;
	double	size_y;

	size_x = (WIDTH + 0.0) / MAP_X / cub3d->data.width;
	size_y = (HEIGHT + 0.0) / MAP_Y / cub3d->data.height;
	if (size_x < size_y)
		return (size_x);
	return (size_y);
}

static int	get_color(t_cub3d *cub3d, int map_x, int map_y)
{
	int	x;
	int	y;
	int	tile;

	x = map_x / ((cub3d->mlx.map_img->width + 0.0) / cub3d->data.width);
	y = map_y / ((cub3d->mlx.map_img->height + 0.0) / cub3d->data.height);
	tile = cub3d->data.map[y][x];
	if (tile == '1')
		return (MAP_WALL_COLOR);
	if (tile == '0')
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
			mlx_put_pixel(cub3d->mlx.map_img, x, y, get_color(cub3d, x, y));
	}
}

static void	draw_player(t_cub3d *cub3d, double size)
{
	int	player[2];
	int	x;
	int	y;

	player[0] = ((cub3d->mlx.player.y + 0.0) / TILE_SIZE) * size;
	player[1] = ((cub3d->mlx.player.x + 0.0) / TILE_SIZE) * size;
	y = player[0] - size / 4;
	while (++y < player[0] + size / 4)
	{
		x = player[1] - size / 4;
		while (++x < player[1] + size / 4)
		{
			if (x < 0 || y < 0)
				continue ;
			mlx_put_pixel(cub3d->mlx.map_img, x, y, MAP_PLAYER_COLOR);
		}
	}
}

void	minimap(t_cub3d *cub3d)
{
	double	size;

	size = get_size(cub3d);
	cub3d->mlx.map_img = mlx_new_image(cub3d->win,
			size * cub3d->data.width, size * cub3d->data.height);
	if (!cub3d->mlx.map_img)
		ft_put_error(cub3d, "MLX new image", false);
	draw_map(cub3d);
	draw_player(cub3d, size);
	if (mlx_image_to_window(cub3d->win, cub3d->mlx.map_img, 0, 0) < 0)
		ft_put_error(cub3d, "MLX image to win", false);
}
