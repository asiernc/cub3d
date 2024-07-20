/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <molasz-a@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:32:35 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/20 17:05:14 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_front(t_player_mlx *player, char **map)
{
	int	x;
	int	y;
	int	nx;
	int	ny;

	x = (player->pos.x + player->dir.x * MOVE_SPEED) / TILE_SIZE + 0.2;
	y = (player->pos.y + player->dir.y * MOVE_SPEED) / TILE_SIZE + 0.2;
	nx = (player->pos.x + player->dir.x * MOVE_SPEED) / TILE_SIZE - 0.2;
	ny = (player->pos.y + player->dir.y * MOVE_SPEED) / TILE_SIZE - 0.2;
	if (map[player->pos.y / TILE_SIZE][x] == '0'
			&& map[player->pos.y / TILE_SIZE][nx] == '0')
		player->pos.x += player->dir.x * MOVE_SPEED;
	if (map[y][player->pos.x / TILE_SIZE] == '0'
			&& map[ny][player->pos.x / TILE_SIZE] == '0')
		player->pos.y += player->dir.y * MOVE_SPEED;
}

void	move_back(t_player_mlx *player, char **map)
{
	int	x;
	int	y;
	int	nx;
	int	ny;

	x = (player->pos.x - player->dir.x * MOVE_SPEED) / TILE_SIZE + 0.2;
	y = (player->pos.y - player->dir.y * MOVE_SPEED) / TILE_SIZE + 0.2;
	nx = (player->pos.x - player->dir.x * MOVE_SPEED) / TILE_SIZE - 0.2;
	ny = (player->pos.y - player->dir.y * MOVE_SPEED) / TILE_SIZE - 0.2;
	if (map[player->pos.y / TILE_SIZE][x] == '0'
			&& map[player->pos.y / TILE_SIZE][nx] == '0')
		player->pos.x -= player->dir.x * MOVE_SPEED;
	if (map[y][player->pos.x / TILE_SIZE] == '0'
			&& map[ny][player->pos.x / TILE_SIZE] == '0')
		player->pos.y -= player->dir.y * MOVE_SPEED;
}

void	move_right(t_player_mlx *player, char **map)
{
	int	x;
	int	y;
	int	nx;
	int	ny;

	x = (player->pos.x - player->dir.y * MOVE_SPEED) / TILE_SIZE + 0.2;
	y = (player->pos.y + player->dir.x * MOVE_SPEED) / TILE_SIZE + 0.2;
	nx = (player->pos.x - player->dir.y * MOVE_SPEED) / TILE_SIZE - 0.2;
	ny = (player->pos.y + player->dir.x * MOVE_SPEED) / TILE_SIZE - 0.2;
	if (map[player->pos.y / TILE_SIZE][x] == '0'
			&& map[player->pos.y / TILE_SIZE][nx] == '0')
		player->pos.x -= player->dir.y * MOVE_SPEED;
	if (map[y][player->pos.x / TILE_SIZE] == '0'
			&& map[ny][player->pos.x / TILE_SIZE] == '0')
		player->pos.y += player->dir.x * MOVE_SPEED;
}

void	move_left(t_player_mlx *player, char **map)
{
	int	x;
	int	y;
	int	nx;
	int	ny;

	x = (player->pos.x + player->dir.y * MOVE_SPEED) / TILE_SIZE + 0.2;
	y = (player->pos.y - player->dir.x * MOVE_SPEED) / TILE_SIZE + 0.2;
	nx = (player->pos.x + player->dir.y * MOVE_SPEED) / TILE_SIZE - 0.2;
	ny = (player->pos.y - player->dir.x * MOVE_SPEED) / TILE_SIZE - 0.2;
	if (map[player->pos.y / TILE_SIZE][x] == '0'
			&& map[player->pos.y / TILE_SIZE][nx] == '0')
		player->pos.x += player->dir.y * MOVE_SPEED;
	if (map[y][player->pos.x / TILE_SIZE] == '0'
			&& map[ny][player->pos.x / TILE_SIZE] == '0')
		player->pos.y -= player->dir.x * MOVE_SPEED;
}

void	move_action(t_cub3d *cub3d)
{
	(void) cub3d;
	printf("ACTION\n");
}
