/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:06:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/18 20:07:16 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*uint32_t	get_color_from_texture(t_cub3d *cub3d, int tex_x,
			int tex_y, int orientation)
{
	return (cub3d->mlx.img_arr[orientation][tex_y][tex_x]);
}*/

void	fill_img(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = 0;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(cub3d->mlx.render_img, x, y, cub3d->data.ceil);
			else
				mlx_put_pixel(cub3d->mlx.render_img, x, y, cub3d->data.floor);
		}
	}
}

void	draw_line(t_cub3d *cub3d, int x, int draw[2], unsigned int color)
{
	int	y;

	y = draw[0] - 1;
	while (++y < draw[1])
		mlx_put_pixel(cub3d->mlx.render_img, x, y, color);
}
