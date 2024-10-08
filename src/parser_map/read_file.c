/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/23 18:03:02 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	read_lines(t_cub3d *cub3d, int *flag_inside, char *line, int fd)
{
	int		width;

	remove_newline(line);
	if (cub3d->data.flag_map)
	{
		if (line[0] == '\0')
			*flag_inside = 1;
		else if (*flag_inside)
		{
			free(line);
			close(fd);
			ft_put_error(cub3d, "Error. Only valid map characters are allowed",
				true);
		}
	}
	if (check_map_line(line) == 1)
	{
		cub3d->data.flag_map = 1;
		width = ft_strlen_map(line);
		if (width > cub3d->data.width)
			cub3d->data.width = width;
		cub3d->data.height++;
		*flag_inside = 0;
	}
	free(line);
}

static void	get_height_width(t_cub3d *cub3d, char *file_path)
{
	char	*line;
	int		fd;
	int		flag_inside;

	flag_inside = 0;
	fd = open(file_path, O_RDONLY, 0644);
	if (fd < 0)
		ft_put_error(cub3d, "Open map file error", false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		read_lines(cub3d, &flag_inside, line, fd);
	}
	close(fd);
	if (cub3d->data.height <= 2 || cub3d->data.width <= 2)
		ft_put_error(cub3d, "Map too small", true);
}

static void	init_map(t_cub3d *cub3d)
{
	cub3d->data.map = ft_calloc(cub3d->data.height + 1, sizeof(char *));
	if (!cub3d->data.map)
		ft_put_error(cub3d, "malloc error", true);
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
			if (cub3d->data.flag_complete == 1 && line[0] != '\0')
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
}
