/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/15 17:11:20 by anovio-c         ###   ########.fr       */
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

static char	*dup_map_line(char *str, int witdh)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	cpy = ft_calloc((witdh + 1), sizeof(char));
	if (!cpy)
		return (NULL);
	ft_memset(cpy, ' ', witdh);
	cpy[witdh] = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			j += 3;
		else
			cpy[j] = str[i];
		i++;
		j++;
	}
	return (cpy);
}

void	fill_map(t_cub3d *cub3d, char *line, int i)
{
	if (i == 0)
		check_required_data_for_map(cub3d);
	if (i == cub3d->data.height - 1)
		cub3d->data.flag_complete = 1;
	cub3d->data.map[i] = dup_map_line(line, cub3d->data.width);
}




