/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/16 12:21:40 by molasz-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

void	get_height_width(t_cub3d *cub3d, char *file_path)
{
	char	*line;
	int		width;
	int		fd;

	fd = open(file_path, O_RDONLY, 0644);
	if (fd < 0)
		ft_put_error(cub3d, "Open map file error", false);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		remove_newline(line);
		if (cub3d->data.height != 0 && !line[0])
			ft_put_error(cub3d, "File letter end error", true);
		if (check_map_line(line) == 1)
		{
			width = ft_strlen_map(line);
			if (width > cub3d->data.width)
				cub3d->data.width = width;
			cub3d->data.height++;
		}
		free(line);
	}
	close(fd);
	if (cub3d->data.height <= 2 || cub3d->data.width <= 2)
		ft_put_error(cub3d, "Map too small", true);
}

int	ft_strlen_map(char *str)
{
	int i;
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
