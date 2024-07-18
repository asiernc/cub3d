/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/18 10:09:28 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	ft_init_textures(t_cub3d *cub3d)
{
	return ;
	texture_to_img(cub3d, cub3d->data.no_path, &cub3d->mlx.no_img);
	texture_to_img(cub3d, cub3d->data.ea_path, &cub3d->mlx.ea_img);
	texture_to_img(cub3d, cub3d->data.so_path, &cub3d->mlx.so_img);
	texture_to_img(cub3d, cub3d->data.we_path, &cub3d->mlx.we_img);
}

static void	texture_to_img(t_cub3d *cub3d, char *path, mlx_image_t *img)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(path);
	if (!xpm)
		ft_put_error(cub3d, "Load XPM error", false);
	img = mlx_texture_to_image(cub3d->win, &xpm->texture);
	if (!img)
		ft_put_error(cub3d, "Transform XPM to IMG error", false);
}

void	init_game_struct(t_cub3d *cub3d)
{
	ft_init_textures(cub3d);
	cub3d->mlx.player.x = (cub3d->data.player.x + 1.0)
		* TILE_SIZE - TILE_SIZE / 2;
	cub3d->mlx.player.y = (cub3d->data.player.y + 1.0)
		* TILE_SIZE - TILE_SIZE / 2;
	cub3d->mlx.player.cam_x = 0;
	cub3d->mlx.player.cam_y = 0;
	if (cub3d->data.player.view == 'N')
		cub3d->mlx.player.cam_y = 1;
	else if (cub3d->data.player.view == 'S')
		cub3d->mlx.player.cam_y = -1;
	else if (cub3d->data.player.view == 'E')
		cub3d->mlx.player.cam_x = 1;
	else if (cub3d->data.player.view == 'W')
		cub3d->mlx.player.cam_x = -1;
}