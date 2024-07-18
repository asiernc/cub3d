/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:32:35 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/18 12:07:23 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_front(t_cub3d *cub3d)
{
	cub3d->mlx.player.pos.y -= TILE_SIZE / 4;
	printf("MOVE FRONT\n");
}

void	move_right(t_cub3d *cub3d)
{
	cub3d->mlx.player.pos.x += TILE_SIZE / 4;
	printf("MOVE RIGHT\n");
}

void	move_back(t_cub3d *cub3d)
{
	cub3d->mlx.player.pos.y += TILE_SIZE / 4;
	printf("MOVE BACK\n");
}

void	move_left(t_cub3d *cub3d)
{
	cub3d->mlx.player.pos.x -= TILE_SIZE / 4;
	printf("MOVE LEFT\n");
}

void	move_action(t_cub3d *cub3d)
{
	(void) cub3d;
	printf("ACTION\n");
}
