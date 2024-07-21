/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/17 09:57:49 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

int	set_orientation(t_cub3d *cub3d)
{
	if (cub3d->render.side == 0)
	{
		if (cub3d->render.ray_dir.x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (cub3d->render.ray_dir.y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

static uint32_t	get_color(mlx_image_t *img, int x, int y)
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	//uint8_t		a;


	r = img->pixels[(y * img->width + x) * 4];
	g = img->pixels[(y * img->width + x) * 4 + 1];
	b = img->pixels[(y * img->width + x) * 4 + 2];
	/*a = 0xFF
	if (img->pixels[(y * img->width + x) * 4 + 3])
		a = img->pixels[(y * img->width + x) * 4 + 3];*/
	color = (r << 24) | (g << 16) | (b << 8) | 0xFF;
	return (color);
}

static void	convert_to_array(t_cub3d *cub3d, mlx_image_t *tmp_img,
			uint32_t ***img_arr)
{
	int	x;
	int	y;

	y = -1;
	(*img_arr) = malloc(65 * sizeof(uint32_t *));
	if (!*img_arr)
		printf("allocation error");
		//ft_put_error &&free render?¿
	while (++y < 65)
	{
		x = -1;
		(*img_arr)[y] = malloc(65 * sizeof(uint32_t));
		if (!(*img_arr)[y])
			printf("allocation error");
			//ft_put error && free render?¿
		while (++x < 65)
		{
			(*img_arr)[y][x] = get_color(tmp_img, x, y);
			//x++;
		}
		printf("color of {%d,%d} is %u\n", 0, y, (*img_arr)[y][0]);
	}
	if (tmp_img)
		mlx_delete_image(cub3d->win, tmp_img);
}
//copy_texture_from_img_to_array(img, &config->img_tab[i], mlx, 64);

// xpm_t* mlx_load_xpm42(const char* path);

int	load_texture(t_cub3d *cub3d)
{
	int			i;
	xpm_t		*xpm;
	mlx_image_t	*tmp_img;

	i = 0;
	while (i < 4)
	{
		if (i == 0)
			xpm = mlx_load_xpm42(cub3d->data.no_path);
		else if (i == 1)
			xpm = mlx_load_xpm42(cub3d->data.so_path);
		else if (i == 2)
			xpm = mlx_load_xpm42(cub3d->data.we_path);
		else if (i == 3)
			xpm = mlx_load_xpm42(cub3d->data.ea_path);
		if (xpm)
			tmp_img = mlx_texture_to_image(cub3d->win, &xpm->texture);
		else
			return (0);
		convert_to_array(cub3d, tmp_img, &cub3d->mlx.img_arr[i]);
		i++;
	}
	//free_textures(cub3d);
	return (1);
}
