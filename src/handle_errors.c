/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:18:21 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/27 18:29:05 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libs/libft/libft.h"

void	ft_put_error(t_cub3d *cub3d, const char *err_msg, bool flag)
{
	if (cub3d)
		ft_free_parser(cub3d);
	if (flag)
		ft_putendl_fd(err_msg, STDERR_FILENO);
	else
		perror(err_msg);
	exit(1);
}

void	ft_free_parser(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (cub3d && cub3d->data.map)
	{
		while (cub3d->data.map[i])
		{
			if (cub3d->data.map[i])
				free(cub3d->data.map[i]);
			i++;
		}
		free(cub3d->data.map);
	}
	if (cub3d && cub3d->data.map_file_path)
		free(cub3d->data.map_file_path);
	if (cub3d->data.no_path)
		free(cub3d->data.no_path);
	if (cub3d->data.so_path)
		free(cub3d->data.so_path);
	if (cub3d->data.ea_path)
		free(cub3d->data.ea_path);
	if (cub3d->data.we_path)
		free(cub3d->data.we_path);
}

static void	free_tex_arr(uint32_t **arr)
{
	int	i;

	i = -1;
	while (++i < TEX_WIDTH)
		free(arr[i]);
	free(arr);
}

static void	ft_free_mlx(t_cub3d *cub3d)
{
	int	i;

	i = -1;
	while (++i < 4)
		free_tex_arr(cub3d->mlx.img_arr[i]);
	if (cub3d->mlx.render_old_img)
		mlx_delete_image(cub3d->win, cub3d->mlx.render_old_img);
	if (cub3d->mlx.map_old_img)
		mlx_delete_image(cub3d->win, cub3d->mlx.map_old_img);
	if (cub3d->mlx.render_img)
		mlx_delete_image(cub3d->win, cub3d->mlx.render_img);
	if (cub3d->mlx.map_img)
		mlx_delete_image(cub3d->win, cub3d->mlx.map_img);
}

void	ft_free_all(t_cub3d *cub3d)
{
	ft_free_parser(cub3d);
	ft_free_mlx(cub3d);
}
