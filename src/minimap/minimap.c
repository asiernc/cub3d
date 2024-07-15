/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:57:44 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/15 13:06:40 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	init_map(t_cub3d *cub3d, int w, int h)
{
	cub3d->mlx.map_img = mlx_new_image(cub3d->win, w, h);
	if (!cub3d->mlx.map_img)
		return ;//error;
}

static int	get_color(t_cub3d *cub3d, int map_x, int map_y)
{
	int	x;
	int	y;
	int	tile;

	x = map_x / ((cub3d->mlx.map_img->width + 0.0) / cub3d->data.width);
	y = map_y / ((cub3d->mlx.map_img->height + 0.0) / cub3d->data.height);
	if (x == cub3d->data.player.x && y == cub3d->data.player.y)
		return (MAP_PLAYER_COLOR);
	tile = cub3d->data.map[y][x];
	if (tile == '1')
		return (MAP_WALL_COLOR);
	if (tile == '0')
		return (MAP_FLOOR_COLOR);
	return (0x00000000);
}

static void	draw_map(t_cub3d *cub3d)
{
	int		x;
	int		y;

	y = -1;
	while (++y < (int)cub3d->mlx.map_img->height)
	{
		x = -1;
		while (++x < (int)cub3d->mlx.map_img->width)
			mlx_put_pixel(cub3d->mlx.map_img, x, y, get_color(cub3d, x , y));
	}
}

void	minimap(t_cub3d *cub3d)
{
	if (cub3d->data.width < cub3d->data.height)
		init_map(cub3d, WIDTH / MAP_X, HEIGHT / MAP_X);
	else
		init_map(cub3d, WIDTH / MAP_Y, HEIGHT / MAP_Y);
	draw_map(cub3d);
	if (mlx_image_to_window(cub3d->win, cub3d->mlx.map_img, 0, 0) < 0)
        return ;	
}
