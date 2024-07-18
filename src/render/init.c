/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/18 15:58:39 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	texture_to_img(t_cub3d *cub3d, char *path, mlx_image_t *img)
{
	xpm_t	*xpm;

	return ;
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		ft_put_error(cub3d, "Load XPM error", false);
	img = mlx_texture_to_image(cub3d->win, &xpm->texture);
	if (!img)
		ft_put_error(cub3d, "Transform XPM to IMG error", false);
}

static void	init_player_dir(t_cub3d *cub3d)
{
	cub3d->mlx.player.dir.x = 0;
	cub3d->mlx.player.dir.y = 0;
	cub3d->mlx.player.plane.x = 0;
	cub3d->mlx.player.plane.y = 0;
	if (cub3d->data.player.view == 'N')
	{
		cub3d->mlx.player.dir.y = -1;
		cub3d->mlx.player.plane.x = 0.66;
	}
	else if (cub3d->data.player.view == 'S')
	{
		cub3d->mlx.player.dir.y = 1;
		cub3d->mlx.player.plane.x = -0.66;
	}
	else if (cub3d->data.player.view == 'E')
	{
		cub3d->mlx.player.dir.x = 1;
		cub3d->mlx.player.plane.y = 0.66;
	}
	else if (cub3d->data.player.view == 'W')
	{
		cub3d->mlx.player.dir.x = -1;
		cub3d->mlx.player.plane.y = -0.66;
	}
}

void	init_game_struct(t_cub3d *cub3d)
{
	texture_to_img(cub3d, cub3d->data.no_path, &cub3d->mlx.no_img);
	texture_to_img(cub3d, cub3d->data.ea_path, &cub3d->mlx.ea_img);
	texture_to_img(cub3d, cub3d->data.so_path, &cub3d->mlx.so_img);
	texture_to_img(cub3d, cub3d->data.we_path, &cub3d->mlx.we_img);
	cub3d->mlx.player.pos.x = (cub3d->data.player.pos.x + 1.0)
		* TILE_SIZE - TILE_SIZE / 2;
	cub3d->mlx.player.pos.y = (cub3d->data.player.pos.y + 1.0)
		* TILE_SIZE - TILE_SIZE / 2;
	init_player_dir(cub3d);
}
