/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:33:46 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/05 12:36:35 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	test_print(t_data *data)
{
	printf("NO PATH => %s\n", data->no_path);
	printf("EA PATH => %s\n", data->ea_path);
	printf("SO PATH => %s\n", data->so_path);
	printf("WE PATH => %s\n", data->we_path);
	printf("FLOOR COLOR => %d\n", data->floor);
	printf("CEIL COLOR => %d\n", data->ceil);
}

static int	rgb_to_int(int red, int green, int blue)
{
	int		color;

	color = 0;
	color |= (int)(blue * 255);
	color |= (int)(green * 255) << 8;
	color |= (int)(red * 255) << 16;
	printf("COLORS %d %d %d [%d]\n", red, green, blue, color);
	return (color);
}

static int	read_colors(char **line)
{
	int	color[3];
	int	i;
	int	counter;

	// Check no more than 1 letter on line and no value on data
	i = 1;
	counter = 0;
	while (counter < 3)
		color[counter++] = ft_atoi(line[i++]); // between 0 - 255
	return (rgb_to_int(color[0], color[1], color[2]));
}

static void check_fill_textures(char **key, char *value)
{
	if (*key)
		ft_put_error("Double map key", true);
	*key = ft_strdup(value);
}

static void	ft_fill_data(t_cub3d *cub3d, char **split_line)
{
	if (!ft_strncmp(split_line[0], "NO", 3))
		check_fill_textures(&cub3d->data.no_path, split_line[1]); 
	else if (!ft_strncmp(split_line[0], "SO", 3))
		check_fill_textures(&cub3d->data.so_path, split_line[1]); 
	else if (!ft_strncmp(split_line[0], "WE", 3))
		check_fill_textures(&cub3d->data.we_path, split_line[1]); 
	else if (!ft_strncmp(split_line[0], "EA", 3))
		check_fill_textures(&cub3d->data.ea_path, split_line[1]); 
	else if (!ft_strncmp(split_line[0], "F", 2))
		cub3d->data.floor = read_colors(split_line);
	else if (!ft_strncmp(split_line[0], "C", 2))
		cub3d->data.ceil = read_colors(split_line);
}
static int	ft_check_line(t_cub3d *cub3d, char *line)
{
	char	**split_line;

	split_line = ft_split(line, ' ');
	ft_fill_data(cub3d, split_line);
	test_print(&cub3d->data);
	return (0);
}

void	ft_check_map(t_cub3d *cub3d, char *file_path)
{
	int		fd;
	char	*line;
	char	*clean_line;

	(void)cub3d;
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
		if (line[0] != '\n')
		{
			clean_line = clear_input_line(line);
			printf("LINE CLEAN %s\n", clean_line);
			if (ft_check_line(cub3d, clean_line))
			{
				free(clean_line);
				ft_put_error("Fill error", true);
			}
		}
		free(line);
		free(clean_line);
	}
	close(fd);
}
