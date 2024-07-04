/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:56 by asiercara         #+#    #+#             */
/*   Updated: 2024/07/04 15:46:20 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// static void	ft_init_window(t_cub3d *cub3d)
// {
// 	cub3d->mlx = mlx_init();
// 	if (!cub3d->mlx)
// 		ft_put_error("Error establishing a connection to the graphics system.",
// 			true);
// 	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "cub3d");
// 	if (!cub3d->win)
// 		ft_put_error("Error initializing window.", true);
// }

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		ft_put_error("Wrong arguments", true);
	ft_check_map(&cub3d, argv[1]);
	//ft_init_window(&cub3d);
	//mlx_loop(cub3d.mlx);
	return (0);
}
