/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:56 by asiercara         #+#    #+#             */
/*   Updated: 2024/07/23 18:11:40 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static void	init_structs(t_cub3d *cub3d)
{
	cub3d->time = -1;
	cub3d->mlx.mouse_x = -1;
	cub3d->mlx.player.pos.x = (cub3d->data.player.pos.x + 1.0)
		* TILE_SIZE - TILE_SIZE / 2;
	cub3d->mlx.player.pos.y = (cub3d->data.player.pos.y + 1.0)
		* TILE_SIZE - TILE_SIZE / 2;
	cub3d->mlx.render_img = NULL;
	cub3d->mlx.render_old_img = NULL;
}

static void	ft_init_mlx(t_cub3d *cub3d)
{
	cub3d->win = mlx_init(WIDTH, HEIGHT, "CUB3D - molasz-a / anovio-c", false);
	if (!cub3d->win)
		ft_put_error(cub3d,
			"Error establishing a connection to the graphics system.", true);
	mlx_key_hook(cub3d->win, &on_key, (void *)cub3d);
	mlx_mouse_hook(cub3d->win, &on_mouse_key, (void *)cub3d);
	mlx_cursor_hook(cub3d->win, &on_mouse_move, (void *)cub3d);
	mlx_loop_hook(cub3d->win, &on_frame, (void *)cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		ft_put_error(NULL, "Wrong arguments", true);
	init_parser_struct(&cub3d.data);
	read_file(&cub3d, argv[1]);
	init_structs(&cub3d);
	init_player_dir(&cub3d);
	ft_init_mlx(&cub3d);
	load_texture(&cub3d);
	init_minimap(&cub3d);
	mlx_loop(cub3d.win);
	mlx_terminate(cub3d.win);
	return (0);
}
