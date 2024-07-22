/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:06:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/22 16:20:01 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*uint32_t	get_color_from_texture(t_cub3d *cub3d, int tex_x,
			int tex_y, int orientation)
{
	return (cub3d->mlx.img_arr[orientation][tex_y][tex_x]);
}*/

void	draw_line(t_cub3d *cub3d, int x, int draw[2], unsigned int color)
{
	int	y;

	y = 0;
	while (++y < HEIGHT)
	{
		if (y > draw[0] && y < draw[1])
			mlx_put_pixel(cub3d->mlx.render_img, x, y, color);
		else if (y < HEIGHT / 2)
			mlx_put_pixel(cub3d->mlx.render_img, x, y, cub3d->data.ceil);
		else
			mlx_put_pixel(cub3d->mlx.render_img, x, y, cub3d->data.floor);
	}
}
