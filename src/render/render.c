/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:01:11 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/29 11:58:02 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

static void	init_values(t_cub3d *cub3d, int x)
{
	double		camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	cub3d->render.ray_dir.x = cub3d->mlx.player.dir.x
		+ cub3d->mlx.player.plane.x * camera_x;
	cub3d->render.ray_dir.y = cub3d->mlx.player.dir.y
		+ cub3d->mlx.player.plane.y * camera_x;
	cub3d->render.map.x = (int)cub3d->render.player.x;
	cub3d->render.map.y = (int)cub3d->render.player.y;
	cub3d->render.delta_dist.x = 1e30;
	cub3d->render.delta_dist.y = 1e30;
	if (cub3d->render.ray_dir.x)
		cub3d->render.delta_dist.x = fabs(1 / cub3d->render.ray_dir.x);
	if (cub3d->render.ray_dir.y)
		cub3d->render.delta_dist.y = fabs(1 / cub3d->render.ray_dir.y);
	cub3d->render.hit = 0;
	cub3d->render.side = 0;
}

static void	set_direction(t_render *render)
{
	if (render->ray_dir.x < 0)
	{
		render->step.x = -1;
		render->side_dist.x = (render->player.x - render->map.x)
			* render->delta_dist.x;
	}
	else
	{
		render->step.x = 1;
		render->side_dist.x = (render->map.x + 1.0 - render->player.x)
			* render->delta_dist.x;
	}
	if (render->ray_dir.y < 0)
	{
		render->step.y = -1;
		render->side_dist.y = (render->player.y - render->map.y)
			* render->delta_dist.y;
	}
	else
	{
		render->step.y = 1;
		render->side_dist.y = (render->map.y + 1.0 - render->player.y)
			* render->delta_dist.y;
	}
}

static void	dda(t_cub3d *cub3d)
{
	while (!cub3d->render.hit)
	{
		if (cub3d->render.side_dist.x < cub3d->render.side_dist.y)
		{
			cub3d->render.side_dist.x += cub3d->render.delta_dist.x;
			cub3d->render.map.x += cub3d->render.step.x;
			cub3d->render.side = 0;
		}
		else
		{
			cub3d->render.side_dist.y += cub3d->render.delta_dist.y;
			cub3d->render.map.y += cub3d->render.step.y;
			cub3d->render.side = 1;
		}
		if (cub3d->data.map[cub3d->render.map.y][cub3d->render.map.x] != '0')
			cub3d->render.hit = 1;
	}
	if (cub3d->render.side == 0)
		cub3d->render.perp_wall_dist = cub3d->render.side_dist.x
			- cub3d->render.delta_dist.x;
	else
		cub3d->render.perp_wall_dist = cub3d->render.side_dist.y
			- cub3d->render.delta_dist.y;
}

static void	calc_texture(t_cub3d *cub3d)
{
	double	wall_x;

	cub3d->render.line_height = (int)(HEIGHT / cub3d->render.perp_wall_dist);
	cub3d->render.draw_start = -cub3d->render.line_height / 2 + HEIGHT / 2;
	if (cub3d->render.draw_start < 0)
		cub3d->render.draw_start = 0;
	cub3d->render.draw_end = cub3d->render.line_height / 2 + HEIGHT / 2;
	if (cub3d->render.draw_end >= HEIGHT)
		cub3d->render.draw_end = HEIGHT - 1;
	cub3d->render.orientation = set_orientation(cub3d);
	if (cub3d->render.side == 0)
		wall_x = cub3d->render.player.y + cub3d->render.perp_wall_dist
			* cub3d->render.ray_dir.y;
	else
		wall_x = cub3d->render.player.x + cub3d->render.perp_wall_dist
			* cub3d->render.ray_dir.x;
	wall_x -= floor(wall_x);
	cub3d->render.tex_x = wall_x * TEX_WIDTH;
	if ((cub3d->render.side == 0 && cub3d->render.ray_dir.x > 0)
		|| (cub3d->render.side == 1 && cub3d->render.ray_dir.y < 0))
		cub3d->render.tex_x = TEX_WIDTH - cub3d->render.tex_x - 1;
}

void	render(t_cub3d *cub3d)
{
	int			x;

	cub3d->render.player.x = cub3d->mlx.player.pos.x / (double)TILE_SIZE;
	cub3d->render.player.y = cub3d->mlx.player.pos.y / (double)TILE_SIZE;
	x = -1;
	while (++x < WIDTH)
	{
		init_values(cub3d, x);
		set_direction(&cub3d->render);
		dda(cub3d);
		calc_texture(cub3d);
		draw_line(cub3d, x);
	}
}
