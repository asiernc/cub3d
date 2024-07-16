/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:56 by asiercara         #+#    #+#             */
/*   Updated: 2024/07/16 14:44:09 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_data_struct(t_data *data)
{
	data->map = NULL;
	data->height = 0;
	data->width = 0;
	data->no_path = NULL;
	data->ea_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->map_file_path = NULL;
	data->ceil = 4294967295;
	data->floor = 4294967295;
	data->flag_complete = 0;
}

static void	texture_to_img(t_cub3d *cub3d, char *path, mlx_image_t *img)
{
	xpm_t	*xpm;

	printf("Try to open %s\n", path);
	xpm = mlx_load_xpm42(path);
	if (!xpm)
		ft_put_error(cub3d, "Load XPM error", false);
	img = mlx_texture_to_image(cub3d->win, &xpm->texture);
	if (!img)
		ft_put_error(cub3d, "Transform XPM to IMG error", false);
}

static void	ft_init_textures(t_cub3d *cub3d)
{
	return ;
	texture_to_img(cub3d, cub3d->data.no_path, &cub3d->mlx.no_img);
	texture_to_img(cub3d, cub3d->data.ea_path, &cub3d->mlx.ea_img);
	texture_to_img(cub3d, cub3d->data.so_path, &cub3d->mlx.so_img);
	texture_to_img(cub3d, cub3d->data.we_path, &cub3d->mlx.we_img);
}

static void	init_mlx_struct(t_cub3d *cub3d)
{
	ft_init_textures(cub3d);
	cub3d->mlx.player.x = (cub3d->data.player.x + 1.0) * TILE_SIZE - TILE_SIZE / 2;
	cub3d->mlx.player.y = (cub3d->data.player.y + 1.0) * TILE_SIZE - TILE_SIZE / 2;
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

static void	ft_init_mlx(t_cub3d *cub3d)
{
	cub3d->win = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!cub3d->win)
		ft_put_error(cub3d, "Error establishing a connection to the graphics system.",
			true);
	mlx_key_hook(cub3d->win, &on_key, (void *)cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		ft_put_error(NULL, "Wrong arguments", true);
	init_data_struct(&cub3d.data);
	read_file(&cub3d, argv[1]);
	init_mlx_struct(&cub3d);
	ft_init_mlx(&cub3d);
	minimap(&cub3d);
	mlx_loop(cub3d.win);
	mlx_terminate(cub3d.win);
	return (0);
}


