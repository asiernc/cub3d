/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/15 16:55:06 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	init_map(t_cub3d *cub3d)
{
	cub3d->data.map = malloc(sizeof(char *) * (cub3d->data.height + 1));
	if (!cub3d->data.map)
		ft_put_error(cub3d, "malloc error", true);
	cub3d->data.map[cub3d->data.height] = NULL;
}

static void	check_open_file(t_cub3d *cub3d, char *file_path)
{
	if (!ft_strnstr_end(file_path, ".cub"))
		ft_put_error(cub3d, "Map file type is not .cub", true);
	cub3d->data.map_file_path = ft_strdup(file_path);
	get_height_width(cub3d, file_path);
	cub3d->data.fd = open(file_path, O_RDONLY, 0644);
	if (cub3d->data.fd < 0)
		ft_put_error(cub3d, "Open map file error", false);
	init_map(cub3d);
}

void	read_file(t_cub3d *cub3d, char *file_path)
{
	char	*line;
	int		i;

	check_open_file(cub3d, file_path);
	i = 0;
	while (1)
	{
		line = get_next_line(cub3d->data.fd);
		if (!line)
			break ;
		if (line[0] != '\n')
		{
			remove_newline(line);
			printf("VALOR DE I %d\n", i);
			if (cub3d->data.flag_complete == 1)
				ft_put_error(cub3d, "file letter end", true);
			if (!check_map_line(line))
				fill_data(cub3d, line);
			else if (check_map_line(line))
				fill_map(cub3d, line, i++);
		}
		free(line);
	}
	close(cub3d->data.fd);
	check_all_data(cub3d);
	test_print(&cub3d->data);
}
