/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/09 11:32:13 by anovio-c         ###   ########.fr       */
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

void	check_player(t_cub3d *cub3d)
{
	int		i;
	int		j;
	int		counter;
	char	**map;

	map = cub3d->data.map;
	i = 0;
	counter = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_isalpha(map[i][j]))
			{
				counter++;
				// substituir letra por 0 y setear info del jugador
			}
			j++;
		}
		i++;
	}
	if (counter != 1)
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
	return (EXIT_SUCCESS);
}
