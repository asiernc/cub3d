/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:32:42 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/22 11:54:33 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

void	cam_right(t_cub3d *cub3d, double rot_speed)
{
	double	dir_x;
	double	plane_x;

	dir_x = cub3d->mlx.player.dir.x;
	cub3d->mlx.player.dir.x = dir_x * cos(rot_speed) - cub3d->mlx.player.dir.y
		* sin(rot_speed);
	cub3d->mlx.player.dir.y = dir_x * sin(rot_speed) + cub3d->mlx.player.dir.y
		* cos(rot_speed);
	plane_x = cub3d->mlx.player.plane.x;
	cub3d->mlx.player.plane.x = plane_x * cos(rot_speed)
		- cub3d->mlx.player.plane.y * sin(rot_speed);
	cub3d->mlx.player.plane.y = plane_x * sin(rot_speed)
		+ cub3d->mlx.player.plane.y * cos(rot_speed);
}

void	cam_left(t_cub3d *cub3d, double rot_speed)
{
	double	dir_x;
	double	plane_x;

	dir_x = cub3d->mlx.player.dir.x;
	cub3d->mlx.player.dir.x = dir_x * cos(-rot_speed) - cub3d->mlx.player.dir.y
		* sin(-rot_speed);
	cub3d->mlx.player.dir.y = dir_x * sin(-rot_speed) + cub3d->mlx.player.dir.y
		* cos(-rot_speed);
	plane_x = cub3d->mlx.player.plane.x;
	cub3d->mlx.player.plane.x = plane_x * cos(-rot_speed)
		- cub3d->mlx.player.plane.y * sin(-rot_speed);
	cub3d->mlx.player.plane.y = plane_x * sin(-rot_speed)
		+ cub3d->mlx.player.plane.y * cos(-rot_speed);
}

void	cam_mouse(t_cub3d *cub3d, int x)
{
	if (cub3d->mlx.mouse_x >= 0 && x - cub3d->mlx.mouse_x < 0)
		cam_left(cub3d, MOUSE_ROT_SPEED);
	else
		cam_right(cub3d, MOUSE_ROT_SPEED);
	cub3d->mlx.mouse_x = x;
}
