/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:59:20 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/29 11:59:19 by molasz-a         ###   ########.fr       */
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
	t_cub3d	*cub3d;

	cub3d = data;
	cub3d->mlx.render_img = mlx_new_image(cub3d->win, WIDTH, HEIGHT);
	if (!cub3d->mlx.render_img)
		ft_put_error(cub3d, "MLX new image", false);
	render(cub3d);
	minimap(cub3d);
	if (mlx_image_to_window(cub3d->win, cub3d->mlx.render_img, 0, 0) < 0)
		ft_put_error(cub3d, "MLX image to win", false);
	if (cub3d->mlx.render_old_img)
		mlx_delete_image(cub3d->win, cub3d->mlx.render_old_img);
	cub3d->mlx.render_old_img = cub3d->mlx.render_img;
	cub3d->mlx.render_img = NULL;
}
