/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:18:21 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/11 15:37:35 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libs/libft/libft.h"

void	ft_put_error(t_cub3d *cub3d, const char *err_msg, bool flag)
{
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
	if (cub3d->data.map)
	{
		while (cub3d->data.map[i])
		{
			free(cub3d->data.map[i]);
			i++;
		}
		free(cub3d->data.map);
	}
	if (cub3d->data.map_file_path)
		free(cub3d->data.map_file_path);
	// why double-free when I want free path textures
}

void	ft_free_all(t_cub3d *cub3d)
{
	(void)cub3d;
}
