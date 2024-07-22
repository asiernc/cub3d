/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anovio-c <anovio-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:18 by anovio-c          #+#    #+#             */
/*   Updated: 2024/07/22 16:33:46 by anovio-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libs/libft/libft.h"

int	fill_data(t_cub3d *cub3d, char *line)
{
	char	*clean_line;
	char	**split_line;
	int		i;

	clean_line = prepare_line(cub3d, line);
	split_line = ft_split(clean_line, ' ');
	if (!split_line)
		ft_put_error(cub3d, "Malloc error on split", false);
	fill_textures(cub3d, split_line);
	fill_colors(cub3d, split_line);
	i = -1;
	while (split_line[++i])
		free(split_line[i]);
	free(split_line);
	free(clean_line);
	return (0);
}

static void	check_fill_textures(t_cub3d *cub3d, char **key, char *value)
{
	if (*key)
		ft_put_error(cub3d, "Error. Duplicate same texture.", true);
	if (!ft_strnstr_end(value, ".xpm42"))
		ft_put_error(cub3d, "Error. Texture file type is not .xpm42", true);
	*key = ft_strdup(value);
}

void	fill_textures(t_cub3d *cub3d, char **line)
{
	if (!line || !line[0] || !line[1])
		return ;
	if (!ft_strncmp(line[0], "NO", 3))
		check_fill_textures(cub3d, &cub3d->data.no_path, line[1]);
	else if (!ft_strncmp(line[0], "SO", 3))
		check_fill_textures(cub3d, &cub3d->data.so_path, line[1]);
	else if (!ft_strncmp(line[0], "WE", 3))
		check_fill_textures(cub3d, &cub3d->data.we_path, line[1]);
	else if (!ft_strncmp(line[0], "EA", 3))
		check_fill_textures(cub3d, &cub3d->data.ea_path, line[1]);
}
