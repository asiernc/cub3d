/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:59:20 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/08 21:31:56 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/mlx_linux/mlx.h"

int	on_key(int n, t_cub3d *cub3d)
{
	if (n == KEY_ESC)
		on_close(cub3d);
	else if (n == KEY_UP)
		move_front(cub3d);
	else if (n == KEY_RIGHT)
		move_right(cub3d);
	else if (n == KEY_DOWN)
		move_back(cub3d);
	else if (n == KEY_LEFT)
		move_left(cub3d);
	else if (n == KEY_CAM_LEFT)
		cam_left(cub3d);
	else if (n == KEY_CAM_RIGHT)
		cam_right(cub3d);
	return (0);
}

int	on_close(t_cub3d *cub3d)
{
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	ft_free_all(cub3d);
	return (0);
}
