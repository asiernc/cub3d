/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:59:20 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/10 13:21:59 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	on_key(mlx_key_data_t e, void *cub3d)
{
	if (!e.action)
		return ;
	else if (e.key == MLX_KEY_ESCAPE)
		on_close(cub3d);
	else if (e.key == MLX_KEY_W)
		move_front(cub3d);
	else if (e.key == MLX_KEY_D)
		move_right(cub3d);
	else if (e.key == MLX_KEY_S)
		move_back(cub3d);
	else if (e.key == MLX_KEY_A)
		move_left(cub3d);
	else if (e.key == MLX_KEY_LEFT)
		cam_left(cub3d);
	else if (e.key == MLX_KEY_RIGHT)
		cam_right(cub3d);
	else if (e.key == MLX_KEY_SPACE)
		move_action(cub3d);
}

int	on_close(t_cub3d *cub3d)
{
	mlx_close_window(cub3d->win);
	ft_free_all(cub3d);
	return (0);
}
