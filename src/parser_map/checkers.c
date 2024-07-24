/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/24 15:24:35 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

int	check_required_data_for_map(t_cub3d *cub3d)
{
	if (cub3d->data.floor == 4294967295
		|| cub3d->data.ceil == 4294967295)
		ft_put_error(cub3d, "Map data error", true);
	else if (!cub3d->data.no_path || !cub3d->data.we_path
		|| !cub3d->data.ea_path || !cub3d->data.so_path)
		ft_put_error(cub3d, "Missing orientation texture", true);
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
			ft_put_error(NULL, "Invalid char found in the file", true);
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
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				if ((j > 0 && map[i][j - 1] == ' ') ||
					(map[i][j + 1] && map[i][j + 1] == ' ') ||
					(i > 0 && map[i - 1][j] == ' ') ||
					(map[i + 1] && map[i + 1][j] == ' '))
				{
					fprintf(stderr, "Map not closed on {%d, %d}.\n", j, i);
					ft_put_error(cub3d, "Map error.", true);
				}
			}
		}
	}
}

void	check_wall_map(t_cub3d *cub3d, char **map)
{
	int		i;

	i = -1;
	while (++i < cub3d->data.width)
	{
		if (!ft_isspace(map[0][i]) && map[0][i] != '1')
			ft_put_error(cub3d, "Map error: Invalid character on top row.",
				true);
		if (!ft_isspace(map[cub3d->data.height - 1][i])
			&& map[cub3d->data.height - 1][i] != '1')
			ft_put_error(cub3d, "Map error: Invalid character on bottom row.",
				true);
	}
	i = -1;
	while (++i < cub3d->data.height)
	{
		if (!ft_isspace(map[i][0]) && map[i][0] != '1')
			ft_put_error(cub3d, "Map error: Invalid character on left column.",
				true);
		if (!ft_isspace(map[i][cub3d->data.width - 1])
			&& map[i][cub3d->data.width - 1] != '1')
			ft_put_error(cub3d, "Map error: Invalid character on right column.",
				true);
	}
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
		ft_put_error(cub3d, "Map error", true);
	check_wall_map(cub3d, cub3d->data.map);
	check_inside_map(cub3d);
	check_player(cub3d, cub3d->data.map);
	return (EXIT_SUCCESS);
}
