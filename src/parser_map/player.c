/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molasz-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:38:03 by molasz-a          #+#    #+#             */
/*   Updated: 2024/07/23 16:45:03 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	check_in_cross(t_cub3d *cub3d, char **map, int x, int y)
{
	if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
		|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
		ft_put_error(cub3d, "The player is not properly locked", true);
}

static void	replace_player(t_cub3d *cub3d, char **map, int i[3],
		char player_view)
{
	if (i[2] == 1)
	{
		if (i[0] == 0 || i[1] == 0 || i[0] == cub3d->data.width
			|| i[1] == cub3d->data.height)
			ft_put_error(cub3d, "Player in incorrect map position",
				true);
		check_in_cross(cub3d, cub3d->data.map, i[1], i[0]);
		cub3d->data.player.pos.x = i[1];
		cub3d->data.player.pos.y = i[0];
		cub3d->data.player.view = player_view;
		map[i[0]][i[1]] = '0';
	}
	else
		return ;
}

void	check_player(t_cub3d *cub3d, char **map)
{
	int	i[3];

	i[0] = -1;
	i[2] = 0;
	while (map[++i[0]])
	{
		i[1] = -1;
		while (map[i[0]][++i[1]])
		{
			if (ft_isalpha(map[i[0]][i[1]]))
			{
				if (map[i[0]][i[1]] == 'N' || map[i[0]][i[1]] == 'S'
					|| map[i[0]][i[1]] == 'E' || map[i[0]][i[1]] == 'W')
				{
					i[2]++;
					replace_player(cub3d, map, i, map[i[0]][i[1]]);
				}
				else
					ft_put_error(cub3d, "Error. Unidentified player", true);
			}
		}
	}
	if (i[2] != 1)
		ft_put_error(cub3d, "Error only one player", true);
}
