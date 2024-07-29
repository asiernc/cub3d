/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:57:44 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/29 11:56:57 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libs/libft/libft.h"

static void	draw_map(t_cub3d *cub3d)
{
	t_2dvector	coord;
	t_2dvector	max;
	t_2dvector	map;

	max.x = cub3d->mlx.map_size * cub3d->data.width;
	max.y = cub3d->mlx.map_size * cub3d->data.height;
	coord.y = -1;
	while (++coord.y < max.y)
	{
		coord.x = -1;
		while (++coord.x < max.x)
		{
			map.x = coord.x / ((double)max.x / cub3d->data.width);
			map.y = coord.y / ((double)max.y / cub3d->data.height);

			if (cub3d->data.map[map.y][map.x] == '1')
				mlx_put_pixel(cub3d->mlx.render_img, coord.x, coord.y, 
					MAP_WALL_COLOR);
			else if (cub3d->data.map[map.y][map.x] == '0')
				mlx_put_pixel(cub3d->mlx.render_img, coord.x, coord.y,
					MAP_FLOOR_COLOR);
		}
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
			mlx_put_pixel(cub3d->mlx.render_img, x, y, MAP_PLAYER_COLOR);
	}
}

void	minimap(t_cub3d *cub3d)
{
	draw_map(cub3d);
	draw_player(cub3d);
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
}
