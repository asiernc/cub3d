/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:06:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/24 15:57:15 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static uint32_t	get_color(t_cub3d *cub3d, int tex_y)
{
	uint32_t	color;

	color = cub3d->mlx.img_arr[cub3d->render.orientation]
	[tex_y][cub3d->render.tex_x];
	return (color);
}

void	draw_line(t_cub3d *cub3d, int x)
{
	int			y;
	double		step;
	double		tex_pos;
	int			tex_y;

	step = 1.0 * TEX_WIDTH / cub3d->render.line_height;
	tex_pos = (cub3d->render.draw_start - HEIGHT / 2
			+ cub3d->render.line_height / 2) * step;
	y = 0;
	while (++y < HEIGHT)
	{
		if (y > cub3d->render.draw_start && y < cub3d->render.draw_end)
		{
			tex_y = (int)tex_pos & (TEX_WIDTH - 1);
			tex_pos += step;
			mlx_put_pixel(cub3d->mlx.render_img, x, y,
				get_color(cub3d, tex_y));
		}
		else if (y < HEIGHT / 2)
			mlx_put_pixel(cub3d->mlx.render_img, x, y, cub3d->data.ceil);
		else
			mlx_put_pixel(cub3d->mlx.render_img, x, y, cub3d->data.floor);
	}
}
