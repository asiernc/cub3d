/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/04 16:44:28 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static int	rgb_to_int(int red, int green, int blue)
{
	int		color;

	color = 0;
	color |= (int)(blue * 255);
	color |= (int)(green * 255) << 8;
	color |= (int)(red * 255) << 16;
	return (color);
}

static int	read_colors(char *line)
{
	int	color[3];
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (counter < 3)
	{
		while (line[i] && ft_isdigit(line[i]))
			i++;
		color[counter++] = ft_atoi(line + i);
		while (line[i] && !ft_isdigit(line[i]))
			i++;
	}
	return (rgb_to_int(color[0], color[1], color[2]));
}

static void	ft_fill_data(t_cub3d *cub3d, char *line, char **split_line)
{
	if (!ft_strncmp(split_line[0], "NO", 3))
		cub3d->data.no_path = ft_strdup(split_line[1]);
	else if (!ft_strncmp(split_line[0], "SO", 3))
		cub3d->data.so_path = ft_strdup(split_line[1]);
	else if (!ft_strncmp(split_line[0], "WE", 3))
		cub3d->data.we_path = ft_strdup(split_line[1]);
	else if (!ft_strncmp(split_line[0], "EA", 3))
		cub3d->data.ea_path = ft_strdup(split_line[1]);
	else if (!ft_strncmp(split_line[0], "F", 2))
		cub3d->data.floor = read_colors(line);
	else if (!ft_strncmp(split_line[0], "C", 2))
		cub3d->data.ceil = read_colors(line);
}

static int	ft_check_line(t_cub3d *cub3d, char *line)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	printf("%s", line);
	//printf("STR %s, %s   END %s", split_line[0], split_line[1], split_line[2]);
	if (split_line[2] && split_line[2][0] != '\n')
		return (ft_free_double_array(&split_line), 1);
	ft_fill_data(cub3d, line, split_line);
	return (0);
}

void	ft_check_map(t_cub3d *cub3d, char *file_path)
{
	int		fd;
	char	*line;

	if (!ft_strnstr_end(file_path, ".cub"))
		ft_put_error("file type is not .cub", true);
	fd = open(file_path, O_RDONLY, 0644);
	if (fd < 0)
		ft_put_error("Open map file error", false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		clear_line(line);
		printf("LINE CLEAN %s\n", clear_line(line));
		if (ft_check_line(cub3d, line))
		{
			free(line);
			ft_put_error("Fill error", true);
		}
		free(line);
	}
	close(fd);
}
