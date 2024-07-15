/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/14 18:44:31 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	check_open_file(t_cub3d *cub3d, char *file_path)
{
	if (!ft_strnstr_end(file_path, ".cub"))
		ft_put_error("Map file type is not .cub", true);
	cub3d->data.map_file_path = ft_strdup(file_path);
	get_height_width(cub3d, file_path);
	cub3d->data.fd = open(file_path, O_RDONLY, 0644);
	if (cub3d->data.fd < 0)
		ft_put_error("Open map file error", false);
}

static void	init_map(t_cub3d *cub3d)
{
	cub3d->data.map = malloc(sizeof(char *) * (cub3d->data.height + 1));
	if (!cub3d->data.map)
		ft_put_error("malloc error", true);
	cub3d->data.map[cub3d->data.height] = NULL;
}

void	read_file(t_cub3d *cub3d, char *file_path)
{
	char	*line;
	int		y;

	y = 0;
	check_open_file(cub3d, file_path);
	init_map(cub3d);
	while (1)
	{
		line = get_next_line(cub3d->data.fd);
		if (!line)
			break ;
		if (line[0] != '\n')
		{
			remove_newline(line);
			if (!check_map_line(line))
				fill_data(cub3d, line);
			else if (check_map_line(line))
				fill_map(cub3d, line, y++);
		}
		free(line);
	}
	close(cub3d->data.fd);
	check_all_data(cub3d);
	test_print(&cub3d->data);
}
