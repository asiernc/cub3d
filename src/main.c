/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:56 by asiercara         #+#    #+#             */
/*   Updated: 2024/07/09 17:31:42 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libs/mlx_linux/mlx.h"

static void	init_data_struct(t_data *data)
{
	data->map = NULL;
	data->height = 0;
	data->width = 0;
	data->no_path = NULL;
	data->ea_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ceil = 4294967295;
	data->floor = 4294967295;
}

static void	ft_init_window(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		ft_put_error("Error establishing a connection to the graphics system.",
			true);
	cub3d->win = mlx_new_window(cub3d->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub3d->win)
		ft_put_error("Error initializing window.", true);
}

static void	ft_init_events(t_cub3d *cub3d)
{
	mlx_key_hook(cub3d->win, on_key, cub3d);
	mlx_hook(cub3d->win, ON_DESTROY, 0, on_close, cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		ft_put_error("Wrong arguments", true);
	init_data_struct(&cub3d.data);
	read_file(&cub3d, argv[1]);
	ft_init_window(&cub3d);
	ft_init_events(&cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}


