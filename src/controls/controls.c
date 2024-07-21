/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:59:20 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/21 16:27:42 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	on_key(mlx_key_data_t e, void *data)
{
	t_cub3d	*cub3d;

	cub3d = data;
	if (!e.action)
		return ;
	if (e.key == MLX_KEY_ESCAPE)
		on_close(cub3d);
	else if (e.key == MLX_KEY_W)
		move_front(&cub3d->mlx.player, cub3d->data.map);
	else if (e.key == MLX_KEY_D)
		move_right(&cub3d->mlx.player, cub3d->data.map);
	else if (e.key == MLX_KEY_S)
		move_back(&cub3d->mlx.player, cub3d->data.map);
	else if (e.key == MLX_KEY_A)
		move_left(&cub3d->mlx.player, cub3d->data.map);
	else if (e.key == MLX_KEY_LEFT)
		cam_left(cub3d, KEY_ROT_SPEED);
	else if (e.key == MLX_KEY_RIGHT)
		cam_right(cub3d, KEY_ROT_SPEED);
	else if (e.key == MLX_KEY_SPACE)
		move_action(cub3d);
}

void	on_mouse_key(mouse_key_t button, action_t action, modifier_key_t mods,
		void	*cub3d)
{
	(void) mods;
	if (!action)
		return ;
	if (button == MLX_MOUSE_BUTTON_LEFT)
		cam_left(cub3d, KEY_ROT_SPEED);
	else if (button == MLX_MOUSE_BUTTON_RIGHT)
		cam_right(cub3d, KEY_ROT_SPEED);
}

void	on_mouse_move(double x, double y, void *cub3d)
{
	(void)cub3d;
	(void)y;
	cam_mouse(cub3d, x);
}

int	on_close(t_cub3d *cub3d)
{
	mlx_close_window(cub3d->win);
	ft_free_all(cub3d);
	return (0);
}

void	on_frame(void *data)
{
	struct timeval	tv;
	t_cub3d			*cub3d;
	long			time;

	cub3d = data;
	minimap(cub3d);
	render(cub3d);
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	printf("FPS: %ld\n", 1000 / (time - cub3d->time));
	cub3d->time = time;
}
