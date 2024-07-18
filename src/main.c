/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:56 by asiercara         #+#    #+#             */
/*   Updated: 2024/07/18 10:08:46 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	init_parser_struct(&cub3d.data);
	read_file(&cub3d, argv[1]);
	init_game_struct(&cub3d);
	ft_init_mlx(&cub3d);
	minimap(&cub3d);
	mlx_loop(cub3d.win);
	mlx_terminate(cub3d.win);
	return (0);
}
