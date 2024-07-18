/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:01:11 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/18 20:56:29 by molasz-a         ###   ########.fr       */
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

static void	set_draw_values(t_cub3d *cub3d, int x)
{
	int				line_heigth;
	int				draw[2];
	unsigned int	color;

	line_heigth = (int)(HEIGHT / cub3d->render.perp_wall_dist);
	draw[0] = -line_heigth / 2 + HEIGHT / 2;
	if (draw[0] < 0)
		draw[0] = 0;
	draw[1] = line_heigth / 2 + HEIGHT / 2;
	if (draw[1] >= HEIGHT)
		draw[1] = HEIGHT - 1;
	color = WALL_COLOR;
	if (cub3d->render.side)
		color /= 2;
	draw_line(cub3d, x, draw, color);
}

void	render(t_cub3d *cub3d)
{
	int	x;

	fill_img(cub3d);
	cub3d->render.player.x = cub3d->mlx.player.pos.x / 200.0;
	cub3d->render.player.y = cub3d->mlx.player.pos.y / 200.0;
	x = -1;
	while (++x < WIDTH)
	{
		init_values(cub3d, x);
		set_direction(&cub3d->render);
		dda(cub3d);
		set_draw_values(cub3d, x);
	}
	if (mlx_image_to_window(cub3d->win, cub3d->mlx.render_img, 0, 0) < 0)
		ft_put_error(cub3d, "MLX image to win", false);
}
