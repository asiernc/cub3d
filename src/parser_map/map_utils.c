/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/23 15:55:28 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

static void	send_error(t_cub3d *cub3d, int fd, char *line)
{
	free(line);
	close(fd);
	ft_put_error(cub3d, "Error. Only valid map characters are allowed", true);
}

static void	open_file(t_cub3d *cub3d, char *file_path)
{
	int	fd;

	cub3d->data.fd = open(file_path, O_RDONLY, 0644);
	if (fd < 0)
		ft_put_error(cub3d, "Open map file error", false);
}

void	get_height_width(t_cub3d *cub3d, char *file_path)
{
	char	*line;
	int		width;
	int		flag_inside;

	flag_inside = 0;
	open_file(cub3d, file_path);
	while (1)
	{
		line = get_next_line(cub3d->data.fd);
		if (!line)
			break ;
		remove_newline(line);
		if (cub3d->data.flag_map)
		{
			if (line[0] == '\0')
				flag_inside = 1;
			else if (flag_inside)
				send_error(cub3d, cub3d->data.fd, line);
		}
		if (check_map_line(line) == 1)
		{
			cub3d->data.flag_map = 1;
			width = ft_strlen_map(line);
			if (width > cub3d->data.width)
				cub3d->data.width = width;
			cub3d->data.height++;
			flag_inside = 0;
		}
		free(line);
	}
	close(cub3d->data.fd);
	cub3d->data.fd = 0;
	if (cub3d->data.height <= 2 || cub3d->data.width <= 2)
		ft_put_error(cub3d, "Map too small", true);
}

int	ft_strlen_map(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			flag++;
		i++;
	}
	i += flag * 3;
	return (i);
}
