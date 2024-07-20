/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:56 by asiercara         #+#    #+#             */
/*   Updated: 2024/07/20 17:40:12 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_init_mlx(t_cub3d *cub3d)
{
	cub3d->win = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!cub3d->win)
		ft_put_error(cub3d,
			"Error establishing a connection to the graphics system.", true);
	mlx_key_hook(cub3d->win, &on_key, (void *)cub3d);
	mlx_mouse_hook(cub3d->win, &on_mouse_key, (void *)cub3d);
	mlx_cursor_hook(cub3d->win, &on_mouse_move, (void *)cub3d);
	mlx_loop_hook(cub3d->win, &on_frame, (void*)cub3d);
	cub3d->mlx.render_img = mlx_new_image(cub3d->win, WIDTH, HEIGHT);
	if (!cub3d->mlx.render_img)
		ft_put_error(cub3d, "MLX new image", false);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		ft_put_error(NULL, "Wrong arguments", true);
	init_parser_struct(&cub3d.data);
	read_file(&cub3d, argv[1]);
	init_game_struct(&cub3d);
	ft_init_mlx(&cub3d);
	init_minimap(&cub3d);
	render(&cub3d);
	minimap(&cub3d);
	mlx_loop(cub3d.win);
	mlx_terminate(cub3d.win);
	return (0);
}
