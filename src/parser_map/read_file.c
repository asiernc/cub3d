/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/05 12:00:32 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static bool	check_open_file(t_cub3d *cub3d, char *file_path)
{
	if (!ft_strnstr_end(file_path, ".cub"))
		ft_put_error("Map file type is not .cub", true);
	cub3d->data.map_file_path = ft_strdup(file_path);
	get_height_width(cub3d, file_path);
	cub3d->data.fd = open(file_path, O_RDONLY, 0644);
	if (cub3d->data.fd < 0)
		ft_put_error("Open map file error", false);
	return (true);
}

void	read_map(t_cub3d *cub3d, char *file_path)
{
	char	*line;
	char	*clean_line;

	if (!check_open_file(cub3d, file_path))
		ft_put_error("file error", true);
	printf("WITDH %d, HEIGHT %d\n", cub3d->data.width, cub3d->data.height);
	while (1)
	{
		line = get_next_line(cub3d->data.fd);
		if (!line)
			break ;
		if (line[0] != '\n')
		{
			remove_newline(line);
			if (check_map_line(line) == 0)
				clean_line = clear_input_line(line, 0);
			if (check_map_line(line) == 0 && fill_data(cub3d, clean_line))
			{
				free(clean_line);
				ft_put_error("Fill error", true);
			}
			else if (check_map_line(line) == 1)
				fill_map(cub3d, line);
		}
		free(line);
	}
	close(cub3d->data.fd);
	check_all_data(cub3d);
	//test_print(&cub3d->data);
}
