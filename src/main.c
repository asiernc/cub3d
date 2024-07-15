/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:02:56 by asiercara         #+#    #+#             */
/*   Updated: 2024/07/15 17:04:50 by anovio-c         ###   ########.fr       */
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

static void	ft_init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", false);
	if (!cub3d->mlx)
		ft_put_error(cub3d, "Error establishing a connection to the graphics system.",
			true);
	mlx_key_hook(cub3d->mlx, &on_key, (void *)cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	if (argc != 2)
		ft_put_error(NULL, "Wrong arguments", true);
	init_data_struct(&cub3d.data);
	read_file(&cub3d, argv[1]);
	ft_init_mlx(&cub3d);
	mlx_loop(cub3d.mlx);
	mlx_terminate(cub3d.mlx);
	return (0);
}


