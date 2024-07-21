/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:06:28 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/21 16:05:55 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
