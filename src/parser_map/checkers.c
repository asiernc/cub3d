/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/10 12:16:16 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

int	check_required_data_for_map(t_cub3d *cub3d)
{
	if (cub3d->data.floor == 4294967295
		|| cub3d->data.ceil == 4294967295)
		ft_put_error("Map data error", true);
	else if (!cub3d->data.no_path || !cub3d->data.no_path
		|| !cub3d->data.no_path || !cub3d->data.no_path)
		ft_put_error("Missing orientation texture", true);
	return (EXIT_SUCCESS);
}

int	check_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	if (!ft_strncmp(line + i, "NO", 2) || !ft_strncmp(line + i, "SO", 2)
		|| !ft_strncmp(line + i, "WE", 2) || !ft_strncmp(line + i, "EA", 2)
		|| !ft_strncmp(line + i, "F", 1) || !ft_strncmp(line + i, "C", 1))
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	check_inside_map(t_cub3d *cub3d)
{
	char	**map;
	int		i;
	int		j;

	map = cub3d->data.map;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				if (map[i + 1][j] == ' ' || map[i - 1][j] == ' '
					|| map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
				{
					fprintf(stderr, "In {%d, %d} the '0' has not been correctly closed.\n", j, i);
					ft_put_error("Map error.", true);
				}
			j++;
		}
		i++;
	}
}

void	check_wall_map(t_cub3d *cub3d)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = cub3d->data.map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (ft_isspace(map[i][j]))
				j++;
			if ((i == 0 || i == cub3d->data.height - 1) && map[i][j] != '1')
				ft_put_error("Map incorrect position on top/bottom row", true);
			if ((j == 0 || j == cub3d->data.width - 1) && map[i][j] != '1')
				ft_put_error("Map incorrect position on left/right column",
					true);
			j++;
		}
		i++;
	}
}

void	replace_player(t_cub3d *cub3d, char **map, int i[3], char player_view)
{
	if (i[2] == 1)
	{
		cub3d->data.player.x = i[1];
		cub3d->data.player.y = i[0];
		cub3d->data.player.view = player_view;
		map[i[0]][i[1]] = '0';
	}
	else
		return ;
}

 // i[0] == i; i[1] == j; i[2] == counter;

void	check_player(t_cub3d *cub3d)
{
	char	**map;
	int		i[3];

	map = cub3d->data.map;
	i[0] = 0;
	i[2] = 0;
	while (map[i[0]])
	{
		i[1] = 0;
		while (map[i[0]][i[1]])
		{
			if (ft_isalpha(map[i[0]][i[1]]))
			{
				i[2]++;
				replace_player(cub3d, map, i, map[i[0]][i[1]]);
			}
			i[1]++;
		}
		i[0]++;
	}
	if (i[2] != 1)
		ft_put_error("Error Only one player", true);
}


int	check_all_data(t_cub3d *cub3d)
{
	int	flag;

	flag = 0;
	if (cub3d->data.floor == 4294967295
		|| cub3d->data.ceil == 4294967295)
		flag++;
	if (!cub3d->data.no_path || !cub3d->data.ea_path
		|| !cub3d->data.we_path || !cub3d->data.so_path)
		flag++;
	if (!cub3d->data.map)
		flag++;
	if (flag == 3)
		ft_put_error("Map error", true);
	check_wall_map(cub3d);
	check_player(cub3d);
	check_inside_map(cub3d);
	return (EXIT_SUCCESS);
}
