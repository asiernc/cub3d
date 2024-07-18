/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:32:42 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/18 20:57:05 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

void	cam_right(t_cub3d *cub3d)
{
	double	dir_x;
	double	plane_x;

	dir_x = cub3d->mlx.player.dir.x;
	cub3d->mlx.player.dir.x = dir_x * cos(ROT_SPEED) - cub3d->mlx.player.dir.y
		* sin(ROT_SPEED);
	cub3d->mlx.player.dir.y = dir_x * sin(ROT_SPEED) + cub3d->mlx.player.dir.y
		* cos(ROT_SPEED);
	plane_x = cub3d->mlx.player.plane.x;
	cub3d->mlx.player.plane.x = plane_x * cos(ROT_SPEED)
		- cub3d->mlx.player.plane.y * sin(ROT_SPEED);
	cub3d->mlx.player.plane.y = plane_x * sin(ROT_SPEED)
		+ cub3d->mlx.player.plane.y * cos(ROT_SPEED);
}

void	cam_left(t_cub3d *cub3d)
{
	double	dir_x;
	double	plane_x;

	dir_x = cub3d->mlx.player.dir.x;
	cub3d->mlx.player.dir.x = dir_x * cos(-ROT_SPEED) - cub3d->mlx.player.dir.y
		* sin(-ROT_SPEED);
	cub3d->mlx.player.dir.y = dir_x * sin(-ROT_SPEED) + cub3d->mlx.player.dir.y
		* cos(-ROT_SPEED);
	plane_x = cub3d->mlx.player.plane.x;
	cub3d->mlx.player.plane.x = plane_x * cos(-ROT_SPEED)
		- cub3d->mlx.player.plane.y * sin(-ROT_SPEED);
	cub3d->mlx.player.plane.y = plane_x * sin(-ROT_SPEED)
		+ cub3d->mlx.player.plane.y * cos(-ROT_SPEED);
}
