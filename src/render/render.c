/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:01:11 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/18 12:03:55 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

static void	init_values(t_cub3d *cub3d, int x)
{
	double		camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	cub3d->render.ray_dir.x =
		cub3d->mlx.player.dir.x + cub3d->mlx.player.plane.x * camera_x;
	cub3d->render.ray_dir.y =
		cub3d->mlx.player.dir.y + cub3d->mlx.player.plane.y * camera_x;

	cub3d->render.map.x =
		cub3d->mlx.player.pos.x - (cub3d->mlx.player.pos.x % TILE_SIZE);
	cub3d->render.map.y =
		cub3d->mlx.player.pos.y - (cub3d->mlx.player.pos.y % TILE_SIZE);
	cub3d->render.delta_dist.x = 1e30;
	cub3d->render.delta_dist.y = 1e30;
	if (cub3d->render.ray_dir.x)
		cub3d->render.delta_dist.x = fabs(1 / cub3d->render.ray_dir.x); 
	if (cub3d->render.ray_dir.y)
		cub3d->render.delta_dist.y = fabs(1 / cub3d->render.ray_dir.y); 
	cub3d->render.hit = 0;
	cub3d->render.side = 0;
}

static void	set_direction(t_cub3d *cub3d)
{
	if(cub3d->render.ray_dir.x < 0)
	{
		cub3d->render.step.x = -1;
		cub3d->render.side_dist.x = 
			(cub3d->mlx.player.pos.x - cub3d->render.map.x)
			* cub3d->render.delta_dist.x;
	}
	else
	{
		cub3d->render.step.x = 1;
		cub3d->render.side_dist.x = 
			(cub3d->render.map.x + 1.0 - cub3d->mlx.player.pos.x)
			* cub3d->render.delta_dist.x;
	}
	if(cub3d->render.ray_dir.y < 0)
	{
		cub3d->render.step.y = -1;
		cub3d->render.side_dist.y = 
			(cub3d->mlx.player.pos.y - cub3d->render.map.y)
			* cub3d->render.delta_dist.y;
	}
	else
	{
		cub3d->render.step.y = 1;
		cub3d->render.side_dist.y = 
			(cub3d->render.map.y + 1.0 - cub3d->mlx.player.pos.y)
			* cub3d->render.delta_dist.y;
	}
}

void	render(t_cub3d *cub3d)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		init_values(cub3d, x);
		set_direction(cub3d);

	}
}
